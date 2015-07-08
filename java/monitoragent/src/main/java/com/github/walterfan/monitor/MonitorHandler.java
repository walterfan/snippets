package com.github.walterfan.monitor;

public interface MonitorHandler {
	  
	void onMonitorMetrics(MonitorMetrics metrics);
	
	void onMonitorInfo(MonitorInfo info);
}
