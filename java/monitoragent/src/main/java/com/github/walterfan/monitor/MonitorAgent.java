package com.github.walterfan.monitor;

public interface MonitorAgent {
	
	void pushMonitorMetrics(MonitorMetrics metrics);
	
	void setMonitorInfo(MonitorInfo info);
	
	void registerMonitorHandler(MonitorHandler handler);
	
}
