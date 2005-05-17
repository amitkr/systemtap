#include "runtime.h"

/* test of maps with keys of int64 and value of string */

#define KEY1_TYPE INT64
#include "map-keys.c"

#define VALUE_TYPE STRING
#include "map-values.c"

#include "map.c"

int main ()
{
  MAP map = _stp_map_new_int64(4, STRING);

  /* map[1] = one */
  _stp_map_key_int64 (map, 1);
  _stp_map_set_str (map, "one");
  printf ("map[%lld]=%s\n", key1int(map->key), _stp_map_get_str(map));
  _stp_map_print(map,"map");

  /* map[3] = "three" */
  /* try it with macros this time */
  _stp_map_key (map, 3);
  _stp_map_set (map, "three");  
  _stp_map_print (map, "map");


  /* now try to confuse things */
  /* These won't do anything useful, but shouldn't crash */
  _stp_map_key_int64 (map, 0);  
  _stp_map_key_del (map);
  _stp_map_key_int64 (map, 77);  
  _stp_map_key_del (map);
  _stp_map_key_del (map);
  _stp_map_set_str (map,"1000000");

  _stp_map_print (map, "map");

  /* create and delete a key */
  _stp_map_key_int64 (map, 1024);
  _stp_map_set_str (map, "2048");  
  _stp_map_key_int64 (map, 1024);
  _stp_map_key_del (map);

  _stp_map_print (map, "map");

  /* create and delete a key again*/
  _stp_map_key_int64 (map, 1024);
  _stp_map_set_str (map, "2048");  
  _stp_map_key_del (map);

  _stp_map_print (map, "map");

  /* check that unset values are 0 */
  _stp_map_key_int64 (map, 5);
  printf ("map[%lld]=%lld\n", key1int(map->key), _stp_map_get_str(map));

  /* map[5] = "five" */
  _stp_map_set (map, "five");
  _stp_map_print (map, "map");

  /* test empty string */
  _stp_map_set (map, "");
  _stp_map_print (map, "map");


  /* add 4 new entries, pushing the others out */
  int i;
  for (i = 6; i < 10; i++)
    {
      char buf[32];
      sprintf(buf, "value of %d", i);
      _stp_map_key_int64 (map, i);
      _stp_map_set_str (map, buf);
    }

  _stp_map_print (map, "map");  

  /* 5, 382, 526, and 903 all hash to the same value (23) */
  /* use them to test the hash chain */
  _stp_map_key_int64 (map, 5); _stp_map_set_str (map, "1005");
  _stp_map_key_int64 (map, 382); _stp_map_set_str (map, "1382");
  _stp_map_key_int64 (map, 526); _stp_map_set_str (map, "1526");
  _stp_map_key_int64 (map, 903); _stp_map_set_str (map, "1903");

  _stp_map_print (map, "map");  

  /* now delete all 4 nodes, one by one */
  _stp_map_key_int64 (map, 382); _stp_map_key_del (map);

  _stp_map_print (map, "map");  

  _stp_map_key_int64 (map, 5); _stp_map_key_del (map);

  _stp_map_print (map, "map");  

  _stp_map_key_int64 (map, 903); _stp_map_key_del (map);

  _stp_map_print (map, "map");  

  _stp_map_key_int64 (map, 526); _stp_map_key_del (map);

  _stp_map_print (map, "map");  

  _stp_map_del (map);
  return 0;
}
