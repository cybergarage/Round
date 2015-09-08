/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_UTIL_JSON_H_
#define _ROUNDC_UTIL_JSON_H_

#include <round/typedef.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct {
  bool headFlag;
} RoundJSON;

typedef struct {
 bool headFlag;
} RoundJSONObject;
  
/****************************************
 * Functions (JSON)
 ****************************************/

RoundJSON *round_json_new(void);
bool round_json_delete(RoundJSON *json);

/****************************************
 * Functions (JSON Object)
 ****************************************/

RoundJSONObject *round_json_object_new(void);
bool round_json_object_delete(RoundJSONObject *obj);
  
#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif