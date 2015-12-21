/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/script.h>

/****************************************
 * round_script_engine_result2json
 ****************************************/

bool round_script_engine_result2json(RoundString *result, RoundJSONObject** jsonResult, RoundError* err)
{
  *jsonResult = NULL;
  bool isSuccess = false;
  
  RoundJSON* json = round_json_new();
  if (json) {
    isSuccess = round_json_parse(json, round_string_getvalue(result), err);
    if (isSuccess) {
      *jsonResult = round_json_poprootobject(json);
    }
    round_json_delete(json);
  }

  if (!(*jsonResult)) {
    if (0 < round_string_length(result)) {
      isSuccess = true;
      *jsonResult = round_json_string_new(round_string_getvalue(result));
    }
  }

  return isSuccess;
}