package com.github.walterfan.logclient;

import java.util.Date;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import io.netty.buffer.ByteBuf;
import io.netty.buffer.Unpooled;
import io.netty.channel.ChannelHandlerAdapter;
import io.netty.channel.ChannelHandlerContext;

public class LogClientHandler extends ChannelHandlerAdapter {

	private Log logger = LogFactory.getLog(LogClientHandler.class);

	
	@Override
	public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause)
			throws Exception {
		super.exceptionCaught(ctx, cause);
		ctx.close();
	}

	@Override
	public void channelReadComplete(ChannelHandlerContext ctx) throws Exception {
		super.channelReadComplete(ctx);
		ctx.flush();
	}

	@Override
	public void channelActive(ChannelHandlerContext ctx) throws Exception {
		String msg = "[" + new Date(System.currentTimeMillis()).toString() + "] This is a test log";
		ByteBuf buf = Unpooled.buffer(msg.length());
		buf.writeBytes(msg.getBytes());
		
		ctx.writeAndFlush(buf);
	}
	
	
	@Override
	public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
		ByteBuf buf = (ByteBuf)msg;
		byte[] req = new byte[buf.readableBytes()];
		buf.readBytes(req);
		
		String body = new String(req, "UTF-8");
		System.out.println("received " + body);
		
	}
}
