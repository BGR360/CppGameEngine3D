#ifndef BENGINE_ENGINE_H
#define BENGINE_ENGINE_H

#ifdef GAMEENGINE_EXPORTING
#define ENGINE_DLL_EXPORT_IMPORT __declspec(dllexport)
#define ENGINE_DLL_EXPORT __declspec(dllexport)
#else //GAMEENGINE_EXPORTING
#define ENGINE_DLL_EXPORT_IMPORT __declspec(dllimport)
#define ENGINE_DLL_EXPORT
#endif //GAMEENGINE_EXPORTING

#ifdef GAMEENGINE_TESTING
#ifdef GAMEENGINE_EXPORTING
#define ENGINE_DLL_TESTING_ONLY __declspec(dllexport)
#else  //GAMEENGINE_EXPORTING
#define ENGINE_DLL_TESTING_ONLY __declspec(dllimport)
#endif //GAMEENGINE_EXPORTING
#else //GAMEENGINE_TESTING
#define ENGINE_DLL_TESTING_ONLY
#endif //GAMEENGINE_TESTING


#endif //BENGINE_ENGINE_H