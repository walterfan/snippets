package com.github.walterfan.server.logger;

import com.github.walterfan.server.logger.message.ResultMessage;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IoSession;

public class LogClientIoHandler extends IoHandlerAdapter {
	private static Log logger = LogFactory.getLog(LogClientIoHandler.class);
	private com.github.walterfan.server.logger.ResultListener listener;
	
	public LogClientIoHandler(com.github.walterfan.server.logger.ResultListener pListener) {
		this.listener = pListener;
	}
	
	public void sessionOpened(IoSession session) throws Exception {
		logger.info("session opened");
	}

	public void sessionClosed(IoSession session) throws Exception {
		logger.info("session closed");
	}

	public void messageReceived(IoSession session, Object message)
			throws Exception {
		ResultMessage msg = (ResultMessage) message;
		if (msg != null) {
			//logger.info("receive response: " + response.toString());
			this.listener.onResult(msg);
		} else {
			logger.error("receive nothing");
		}
	}

	public void exceptionCaught(IoSession session, Throwable cause)
			throws Exception {
		this.listener.onException(cause);
	}
}
