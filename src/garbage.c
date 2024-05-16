#include <Python.h>
#include "garbage.h"

void garbage_init(void)
{
    Py_Initialize(); //初始化

    //当前路径添加到sys.path中
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("."));
}

void garbage_final(void)
{
    // 关闭Python解释器
    Py_Finalize();
}


char *garbage_category (char *category)
{


    //导入nogarbage模块
    PyObject *pModule = PyImport_ImportModule("garbage");
    if (!pModule) 
    {
        PyErr_Print();
        printf("Error: failed to load garbage.py\n");
        goto FAILED_MODULE;
    }


    //获取alibaba_garbage函数对象
    PyObject *pFunc = PyObject_GetAttrString(pModule, "alibaba_garbage");
    if (!pFunc) 
    {
        PyErr_Print();
        printf("Error: failed to load alibaba_garbage\n");
        goto FAILED_FUNC;
    }


    //调用alibaba_garbage函数并获取返回值
    PyObject *pValue = PyObject_CallObject(pFunc, NULL);
    if (!pValue) 
    {
        PyErr_Print();
        printf("Error: function call failed\n");
        goto FAILED_VALUE;
    }

    //将返回值转换为C类型
    char *result = NULL;

    if (!PyArg_Parse(pValue, "s", &result))
    {
        PyErr_Print();
        printf("Error: parse failed");
        goto FAILED_RESULT;
    }

    //打印返回值
    printf("result = %s\n", result);

    category = (char *)malloc(sizeof(char) * (strlen(result) + 1));
    memset(category, 0, (strlen(result) + 1));

    strncpy(category, result, (strlen(result) + 1));

    // 释放所有引用的Python对象
FAILED_RESULT:
    Py_DECREF(pValue);
FAILED_VALUE:    
    Py_DECREF(pFunc);
FAILED_FUNC:
    Py_DECREF(pModule);
FAILED_MODULE:


    return category;

}
