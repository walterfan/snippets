#pragma once
#ifndef __CPARAMS_H__
#define __CPARAMS_H__

typedef long CmResult;

typedef struct
{
    string m_name;
    string m_value;
    int m_type;
    int index;
} CParam;

typedef map<String,CParam *> CParamContainer;
typedef CParamContainer::iterator ParamsIter;

class CParams
{
public:
	CParams(void);
	~CParams(void);
	CmResult SetParam(const string name, const string value);

	CmResult GetParam(const string name, string& value) const;

	CmResult RemoveParam(const string name);
};

#endif