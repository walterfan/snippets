package com.github.walterfan.circonus;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.sql.SQLException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;
import java.util.TimeZone;

public class App {

	private static final String CALL_IN_COUNT = "call_out_count";

	private static String CIRCONUS_HOST = "10.252.223.72";//"10.254.56.139";//"10.224.57.202";

	private static int CIRCONUS_PORT = 8125;
	private static int TIMEOUT = 5000;

	public static void main(String[] args) {
		try {
			//sendData(CALL_IN_COUNT, 0 ,100);
			StatsdClient client = new StatsdClient(CIRCONUS_HOST, CIRCONUS_PORT);
			client.gauge(CALL_IN_COUNT, 10);
			client.increment(CALL_IN_COUNT);
			client.startFlushTimer(2000);

			System.out.println("--- send packet -- ");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void sendData(String name, int min, int max)
			throws SQLException, IOException {
		String dailyNumber = getDailyNumber();
		// Connect Circonus
		InetSocketAddress ips = new InetSocketAddress(CIRCONUS_HOST, CIRCONUS_PORT);
		DatagramSocket ds = new DatagramSocket();
		DatagramPacket dp_send = null;
		ds.setSoTimeout(TIMEOUT);
		// int i = 0;
		while (System.in.available() == 0) {
			// Send num of siteID
			String str_send_num = name + ":" + randInt(0, 100) + "|g";
			dp_send = new DatagramPacket(str_send_num.getBytes(),
					str_send_num.length(), ips);
			ds.send(dp_send);
			System.out.println("[" + dailyNumber + "] Send " + str_send_num);
			try {
				Thread.sleep(1 * 60 * 1000);
				// i++;
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		ds.close();
		System.out.println("The End");
	}

	public static String getDailyNumber() {
		// Set time to GMT time
		TimeZone local = TimeZone.getDefault();
		TimeZone.setDefault(TimeZone.getTimeZone("GMT"));

		// Get currentdailyNumber
		DateFormat df = new SimpleDateFormat("yyyyMMdd");
		String dailyNumber = df.format(new Date());

		// Restore time
		TimeZone.setDefault(local);

		return dailyNumber;
	}

	/**
	 * Returns a pseudo-random number between min and max, inclusive. The
	 * difference between min and max can be at most
	 * <code>Integer.MAX_VALUE - 1</code>.
	 *
	 * @param min
	 *            Minimum value
	 * @param max
	 *            Maximum value. Must be greater than min.
	 * @return Integer between min and max, inclusive.
	 * @see java.util.Random#nextInt(int)
	 */
	public static int randInt(int min, int max) {

		// NOTE: Usually this should be a field rather than a method
		// variable so that it is not re-seeded every call.
		Random rand = new Random();

		// nextInt is normally exclusive of the top value,
		// so add 1 to make it inclusive
		int randomNum = rand.nextInt((max - min) + 1) + min;

		return randomNum;
	}
}
