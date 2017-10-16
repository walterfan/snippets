/*
 * MonitorHandler.h
 *
 *  Created on: Jul 24, 2015
 *      Author: Walter Fan
 *
 *  TODO: change return value tyep to CmResult
 */

#ifndef _WFAN_MONITORAGENT_H_
#define _WFAN_MONITORAGENT_H_

#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;

typedef enum {
    UNKNOWN = 0,
    CPU,
    MEM,
    DISK.
    BANDWIDTH,
    LATENCY,
    PERFORMANCE
    CAPACITY, 
    MISC
} metrics_type_t;

struct MonitorMetrics
{
public:
    MonitorMetrics() :metricsType(UNKNOWN), metricsKey("")
    { }
    string toString();


    std::string GetValue(std::string strKey)
    {
        std::map<std::string, std::string>::iterator it = metricsMap.find(strKey);
        if (it != metricsMap.end())
        {
            return it->second;
        }

        return "";
    }

    metrics_type_t metricsType;
    std::string        metricsKey;
    long               timestamp;
    std::map<std::string, std::string> metricsMap;

};

class IMetricsHandler
{
public:

    virtual int OnMetrics(MonitorMetrics& metrics) = 0;

    virtual int Initialize() = 0;

    virtual std::string GetName() const = 0;

    virtual ~IMetricsHandler() {}
};


#endif