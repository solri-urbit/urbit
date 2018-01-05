#include "all.h"

static void _setup(void);
static void _test_cache_replace_value(void);
static void _test_cache_trimming(void);
static void _test_no_cache(void);
static void _test_skip_slot(void);

/* main(): run all test cases.
*/
int
main(int argc, char* argv[])
{
  _setup();

  _test_no_cache();
  _test_skip_slot();
  _test_cache_trimming();
  _test_cache_replace_value();

  return 0;
}

/* _setup(): prepare for tests.
*/
static void
_setup(void)
{
  u3m_init(c3y);
  u3m_pave(c3y, c3n);
}

/* _test_no_cache(): test a hashtable without caching.
*/
static void
_test_no_cache(void)
{
  c3_w i_w;
  c3_w max_w = 1000;

  u3p(u3h_root) har_p = u3h_new();

  for ( i_w = 0; i_w < max_w; i_w++ ) {
    u3h_put(har_p, i_w, i_w + max_w);
  }

  for ( i_w = 0; i_w < max_w; i_w++ ) {
    c3_assert(i_w + max_w == u3h_get(har_p, i_w));
  }
  printf("test_no_cache: ok\n");
}

/* _test_skip_slot():
*/
static void
_test_skip_slot(void)
{
  //  root table
  {
    c3_w mug_w = 0x17 << 25;
    c3_w res_w = _ch_skip_slot(mug_w, 25);
    c3_assert((0x18 << 25) == res_w);
  }

  {
    c3_w mug_w = 63 << 25; //  6 bits, all ones
    c3_w res_w = _ch_skip_slot(mug_w, 25);
    c3_assert(0 == res_w);
  }

  //  child nodes
  {
    c3_w mug_w = 17 << 20;
    c3_w res_w = _ch_skip_slot(mug_w, 20);
    c3_assert((18 << 20) == res_w);
  }

  {
    c3_w mug_w = 31 << 20; //  5 bits, all ones
    c3_w res_w = _ch_skip_slot(mug_w, 20);
    c3_assert((1 << 25) == res_w);
  }

  fprintf(stderr, "test_skip_slot: ok\n");
}

/* _test_cache_trimming(): ensure a caching hashtable removes stale items.
*/
static void
_test_cache_trimming(void)
{
  c3_w max_w = 620;
  c3_w i_w;

  //u3p(u3h_root) har_p = u3h_new_cache(max_w / 2);
  u3p(u3h_root) har_p = u3h_new_cache(max_w / 10 );
  u3h_root*     har_u = u3to(u3h_root, har_p);

  for ( i_w = 0; i_w < max_w; i_w++ ) {
    u3h_put(har_p, i_w, i_w + max_w);
  }

  if ( ( max_w + max_w - 1) != u3h_get(har_p, max_w - 1) ) {
    fprintf(stderr, "fail\r\n");
    exit(1);
  }
  if ( ( max_w / 10 ) != har_u->use_w ) {
    fprintf(stderr, "fail\r\n");
    exit(1);
  }
  fprintf(stderr, "test_cache_trimming: ok\n");
}

static void
_test_cache_replace_value(void)
{
  c3_w max_w = 100;
  c3_w i_w;

  u3p(u3h_root) har_p = u3h_new_cache(max_w);
  u3h_root*     har_u = u3to(u3h_root, har_p);

  for ( i_w = 0; i_w < max_w; i_w++ ) {
    u3h_put(har_p, i_w, i_w + max_w);
  }

  for ( i_w = 0; i_w < max_w; i_w++ ) {
    u3h_put(har_p, i_w, i_w + max_w + 1);
  }

  if ( (2 * max_w) != u3h_get(har_p, max_w - 1) ) {
    fprintf(stderr, "fail\r\n");
    exit(1);
  }
  if ( max_w != har_u->use_w ) {
    fprintf(stderr, "fail\r\n");
    exit(1);
  }
  fprintf(stderr, "test_cache_replace_value: ok\r\n");
}
