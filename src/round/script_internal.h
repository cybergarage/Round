/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_SCRIPT_INTERNAL_H_
#define _ROUNDC_SCRIPT_INTERNAL_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <round/typedef.h>
#include <round/util/mutex.h>
#include <round/util/strings.h>
#include <round/util/list.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Data Type
 ****************************************/

typedef struct _RoundScript {
  bool headFlag;
  struct _RoundScript *prev;
  struct _RoundScript *next;

  char *lang;
  char *name;
  byte *code;
  size_t codeSize;
} RoundScript, RoundScriptList;

typedef struct _RoundScriptEngine {
  bool headFlag;
  struct _RoundScriptEngine *prev;
  struct _RoundScriptEngine *next;
  
  RoundMutex *mutex;
  char *lang;
  char *result;
  char *error;
} RoundScriptEngine, RoundScriptEngineList;

typedef struct {
  RoundMutex *mutex;
  RoundScriptList *scripts;
  RoundScriptEngineList *engines;
} RoundScriptManager;

/****************************************
 * Function (Script)
 ****************************************/
  
RoundScript *round_script_new();
bool round_script_delete(RoundScript *script);

#define round_script_next(script) ((RoundScript*)round_list_next((RoundList *)script))
#define round_script_remove(script) round_list_remove((RoundList *)script)

#define round_script_setlanguage(script, value) round_strloc(value, &script->lang)
#define round_script_getlanguage(script) (script->lang)

#define round_script_setname(script, value) round_strloc(value, &script->name)
#define round_script_getname(script) (script->name)

bool round_script_setcode(RoundScript *script, byte *code, size_t codeLen);
#define round_script_getcode(script) (script->code)
#define round_script_getcodeSize(script) (script->codeSize)

bool round_script_isvalid(RoundScript *script);
  
/****************************************
 * Function (Script List)
 ****************************************/

RoundScriptList *round_scriptlist_new(void);
bool round_scriptlist_delete(RoundScriptList *scripts);

#define round_scriptlist_clear(scripts) round_list_clear((RoundList *)scripts, (ROUND_LIST_DESTRUCTORFUNC)round_script_delete)
#define round_scriptlist_size(scripts) round_list_size((RoundList *)scripts)
#define round_scriptlist_gets(scripts) (RoundScript *)round_list_next((RoundList *)scripts)
#define round_scriptlist_add(scripts,script) round_list_add((RoundList *)scripts, (RoundList *)script)
  
/****************************************
 * Function (Script Engine)
 ****************************************/
  
RoundScriptEngine *round_script_engine_new();
bool round_script_engine_init(RoundScriptEngine *engine);
bool round_script_engine_clear(RoundScriptEngine *engine);
bool round_script_engine_delete(RoundScriptEngine *engine);
bool round_script_engine_lock(RoundScriptEngine *engine);
bool round_script_engine_unlock(RoundScriptEngine *engine);
  
#define round_script_engine_setlanguage(script, value) round_strloc(value, &engine->lang)
#define round_script_engine_getlanguage(script) (engine->lang)

  bool round_script_engine_setresult(RoundScriptEngine *engine, const char *value);
const char *round_script_engine_getresult(RoundScriptEngine *engine);
  
bool round_script_engine_seterror(RoundScriptEngine *engine, const char *value);
const char *round_script_engine_geterror(RoundScriptEngine *engine);
  
/****************************************
 * Function (Script Engine List)
 ****************************************/
  
RoundScriptEngineList *round_script_enginelist_new(void);
bool round_script_enginelist_delete(RoundScriptEngineList *nodes);
  
#define round_script_enginelist_clear(nodes) round_list_clear((RoundList *)nodes, (ROUND_LIST_DESTRUCTORFUNC)round_script_engine_delete)
#define round_script_enginelist_size(nodes) round_list_size((RoundList *)nodes)
#define round_script_enginelist_gets(nodes) (RoundScriptEngine *)round_list_next((RoundList *)nodes)
#define round_script_enginelist_add(nodes,node) round_list_add((RoundList *)nodes, (RoundList *)node)

/****************************************
 * Function (Script Manager)
 ****************************************/
  
RoundScriptManager *round_script_manager_new();
bool round_script_manager_delete(RoundScriptManager *mgr);

bool round_script_manager_addscript(RoundScriptManager *mgr, RoundScript *script);
RoundScript *round_script_manager_getscriptbyname(RoundScriptManager *mgr, const char *name);

#ifdef  __cplusplus
}
#endif

#endif