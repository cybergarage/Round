/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/method/system_method.h>

/****************************************
 * round_system_method_setmethod
 ****************************************/

bool round_system_method_setmethod(RoundLocalNode* node,
    RoundJSONObject* params,
    RoundJSONObject** result,
    RoundError* err)
{
  const char *name, *lang;
  byte* code;
  size_t codeLen;
  RoundMethod* newMethod;
  bool isAdded;

  if (!round_json_object_ismap(params)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  if (!round_json_map_getstring(params, ROUND_SYSTEM_METHOD_PARAM_NAME, &name)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  if (!round_json_map_getstring(params, ROUND_SYSTEM_METHOD_PARAM_LANGUAGE, &lang)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  if (!round_json_map_getstring(params, ROUND_SYSTEM_METHOD_PARAM_CODE, (const char**)&code)) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INVALID_PARAMS);
    return false;
  }

  codeLen = round_strlen((const char*)code);

  /* TODO : Support Base64
   #define ROUND_SYSTEM_METHOD_PARAM_ENCODE "encode"
   #define ROUND_SYSTEM_METHOD_PARAM_BASE64 "base64"
   // Encode
   int encodeType = Script::ENCODING_NONE;
   std::string encodeTypeStr;
   if (jsonDict->get(METHOD_ENCODE, &encodeTypeStr)) {
   if (encodeTypeStr.compare(METHOD_ENCODE_BASE64)) {
   encodeType = Script::ENCODING_BASE64;
   }
   }
   */

  newMethod = round_method_new();
  if (!newMethod) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    return false;
  }

  round_method_setname(newMethod, name);
  round_method_setlanguage(newMethod, lang);
  round_method_setcode(newMethod, code, codeLen);

  isAdded = round_local_node_setmethod(node, newMethod);
  if (!isAdded) {
    round_error_setjsonrpcerrorcode(err, ROUND_RPC_ERROR_CODE_INTERNAL_ERROR);
    round_method_delete(newMethod);
  }

  return isAdded;
}
