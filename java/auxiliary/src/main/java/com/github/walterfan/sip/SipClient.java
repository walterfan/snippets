package com.github.walterfan.sip;

import gov.nist.javax.sip.SipStackExt;
import gov.nist.javax.sip.clientauthutils.AuthenticationHelper;

import java.text.ParseException;
import java.util.ArrayList;
import java.util.Properties;

import javax.sip.ClientTransaction;
import javax.sip.Dialog;
import javax.sip.DialogState;
import javax.sip.DialogTerminatedEvent;
import javax.sip.IOExceptionEvent;
import javax.sip.InvalidArgumentException;
import javax.sip.ListeningPoint;
import javax.sip.PeerUnavailableException;
import javax.sip.RequestEvent;
import javax.sip.ResponseEvent;
import javax.sip.ServerTransaction;
import javax.sip.SipFactory;
import javax.sip.SipListener;
import javax.sip.SipProvider;
import javax.sip.SipStack;
import javax.sip.TransactionTerminatedEvent;
import javax.sip.address.Address;
import javax.sip.address.AddressFactory;
import javax.sip.address.SipURI;
import javax.sip.header.CSeqHeader;
import javax.sip.header.CallIdHeader;
import javax.sip.header.ContactHeader;
import javax.sip.header.ContentTypeHeader;
import javax.sip.header.FromHeader;
import javax.sip.header.Header;
import javax.sip.header.HeaderFactory;
import javax.sip.header.MaxForwardsHeader;
import javax.sip.header.ToHeader;
import javax.sip.header.ViaHeader;
import javax.sip.message.MessageFactory;
import javax.sip.message.Request;
import javax.sip.message.Response;

import com.github.walterfan.util.RandomUtils;

/**
 * This class is a UAC template. Shootist is the guy that shoots and shootme is
 * the guy that gets shot.
 *
 * @author M. Ranganathan
 * @author Kathleen McCallum
 */

public class SipClient implements SipListener {

    private static final String DOMAIN_NAME = "10.224.57.195";
   
    private static final String TARGET_SERVER = "10.224.57.195:7989";
    
	private static String localHost = "10.140.197.53";
	
	private static int localPort = 7080; 
	
	private static SipProvider sipProvider;
    private static AddressFactory addressFactory;
    private static MessageFactory messageFactory;
    private static HeaderFactory headerFactory;
    private static SipStack sipStack;
    private ContactHeader contactHeader;
    private ListeningPoint udpListeningPoint;
    private ClientTransaction inviteTid;
    private Dialog dialog;
    long invco = 1;
        
    String peerHostPort = TARGET_SERVER;
    String transport = "udp";
   

    public void processRequest(RequestEvent requestReceivedEvent) {
        Request request = requestReceivedEvent.getRequest();
        ServerTransaction serverTransactionId = requestReceivedEvent
                .getServerTransaction();

        System.out.println("\n\nRequest " + request.getMethod()
                + " received at " + sipStack.getStackName()
                + " with server transaction id " + serverTransactionId);

        // We are the UAC so the only request we get is the BYE.
        if (request.getMethod().equals(Request.BYE))
            processBye(request, serverTransactionId);
    }

    public void processBye(Request request,
            ServerTransaction serverTransactionId) {
        try {
            System.out.println("shootist:  got a bye .");
            if (serverTransactionId == null) {
                System.out.println("shootist:  null TID.");
                return;
            }
            Dialog dialog = serverTransactionId.getDialog();
            System.out.println("Dialog State = " + dialog.getState());
            Response response = messageFactory.createResponse(200, request);
            serverTransactionId.sendResponse(response);
            System.out.println("shootist:  Sending OK.");
            System.out.println("Dialog State = " + dialog.getState());

        } catch (Exception ex) {
            ex.printStackTrace();
            System.exit(0);

        }
    }

    public void processResponse(ResponseEvent responseReceivedEvent) {
        System.out.println("Got a response");
        Response response = (Response) responseReceivedEvent.getResponse();
        ClientTransaction tid = responseReceivedEvent.getClientTransaction();
        CSeqHeader cseq = (CSeqHeader) response.getHeader(CSeqHeader.NAME);

        System.out.println("Response received : Status Code = "
                + response.getStatusCode() + " " + cseq);
        if (tid == null) {
            System.out.println("Stray response -- dropping ");
            return;
        }
        System.out.println("transaction state is " + tid.getState());
        System.out.println("Dialog = " + tid.getDialog());
        System.out.println("Dialog State is " + tid.getDialog().getState());

        try {
            if (response.getStatusCode() == Response.OK) {
                if (cseq.getMethod().equals(Request.INVITE)) {
                    Dialog dialog = inviteTid.getDialog();
                    Request ackRequest = dialog.createAck( cseq.getSeqNumber() );
                    System.out.println("Sending ACK");
                    dialog.sendAck(ackRequest);
                } else if (cseq.getMethod().equals(Request.CANCEL)) {
                    if (dialog.getState() == DialogState.CONFIRMED) {
                        // oops cancel went in too late. Need to hang up the
                        // dialog.
                        System.out
                                .println("Sending BYE -- cancel went in too late !!");
                        Request byeRequest = dialog.createRequest(Request.BYE);
                        ClientTransaction ct = sipProvider
                                .getNewClientTransaction(byeRequest);
                        dialog.sendRequest(ct);
                    }
                }
            } /*else if (response.getStatusCode() == Response.PROXY_AUTHENTICATION_REQUIRED
                    || response.getStatusCode() == Response.UNAUTHORIZED) {
                AuthenticationHelper authenticationHelper = 
                    ((SipStackExt) sipStack).getAuthenticationHelper(new AccountManagerImpl(), headerFactory);
                
                inviteTid = authenticationHelper.handleChallenge(response, tid, sipProvider, 5);
             
                inviteTid.sendRequest();
              
                invco++;
            }*/
        } catch (Exception ex) {
            ex.printStackTrace();
            System.exit(0);
        }

    }

    public void processTimeout(javax.sip.TimeoutEvent timeoutEvent) {

        System.out.println("Transaction Time out");
    }

    public void sendCancel() {
        try {
            System.out.println("Sending cancel");
            Request cancelRequest = inviteTid.createCancel();
            ClientTransaction cancelTid = sipProvider
                    .getNewClientTransaction(cancelRequest);
            cancelTid.sendRequest();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public Request createSipRequest(String callId, String sipMethod) throws ParseException,
    InvalidArgumentException {
        String fromName = "140718173";
        String fromSipAddress = DOMAIN_NAME;
        String fromDisplayName = null;

        String toSipAddress = DOMAIN_NAME;
        String toUser = "140718173";
        String toDisplayName = null;

        // create >From Header
        SipURI fromAddress = addressFactory.createSipURI(fromName,
                fromSipAddress);

        Address fromNameAddress = addressFactory.createAddress(fromAddress);
        fromNameAddress.setDisplayName(fromDisplayName);
        FromHeader fromHeader = headerFactory.createFromHeader(fromNameAddress,
                "30bc806257ab0c78");

        // create To Header
        SipURI toAddress = addressFactory.createSipURI(toUser, toSipAddress);
        Address toNameAddress = addressFactory.createAddress(toAddress);
        toNameAddress.setDisplayName(toDisplayName);
        ToHeader toHeader = headerFactory.createToHeader(toNameAddress, null);

        // create Request URI
        SipURI requestURI = addressFactory.createSipURI(null, peerHostPort);

        // Create ViaHeaders
        ArrayList<ViaHeader> viaHeaders = new ArrayList<ViaHeader>();
        ViaHeader viaHeader = headerFactory.createViaHeader(localHost,
                sipProvider.getListeningPoint(transport).getPort(), transport,
                null);
        // add via headers
        viaHeaders.add(viaHeader);

           // Create a new CallId header
        CallIdHeader callIdHeader;
        callIdHeader = sipProvider.getNewCallId();
        if (callId.trim().length() > 0)
            callIdHeader.setCallId(callId);

        // Create a new Cseq header
        CSeqHeader cSeqHeader = headerFactory.createCSeqHeader(invco,
                sipMethod);

        // Create a new MaxForwardsHeader
        MaxForwardsHeader maxForwards = headerFactory
                .createMaxForwardsHeader(70);

        // Create the request.
        Request request = messageFactory.createRequest(requestURI,
                sipMethod, callIdHeader, cSeqHeader, fromHeader, toHeader, viaHeaders, maxForwards);

        
        System.out.println("createSipRequest:  " + sipMethod);
        // Create contact headers
        String host = peerHostPort;

        SipURI contactUrl = addressFactory.createSipURI(null, host);
        contactUrl.setPort(udpListeningPoint.getPort());

        // Create the contact name address.
        SipURI contactURI = addressFactory.createSipURI(null, host);
        contactURI.setPort(sipProvider.getListeningPoint(transport).getPort());

        Address contactAddress = addressFactory.createAddress(contactURI);

        // Add the contact address.
        //contactAddress.setDisplayName(fromName);
        
        contactHeader = headerFactory.createContactHeader(contactAddress);
        contactHeader.setExpires(3600);
        
        request.addHeader(contactHeader);

        ContentTypeHeader contentTypeHeader = headerFactory.createContentTypeHeader("application", "sdp");
        byte[] contents = {};
        request.setContent(contents, contentTypeHeader);
        
        return request;
    }
    

    public Request createInvite(String callId) throws ParseException,
            InvalidArgumentException {
        String fromName = "alice";
        String fromSipAddress = "alicesite.com";
        String fromDisplayName = "alice";

        String toSipAddress = "bobsite.com";
        String toUser = "bob";
        String toDisplayName = "Bob";

        // create >From Header
        SipURI fromAddress = addressFactory.createSipURI(fromName,
                fromSipAddress);

        Address fromNameAddress = addressFactory.createAddress(fromAddress);
        fromNameAddress.setDisplayName(fromDisplayName);
        FromHeader fromHeader = headerFactory.createFromHeader(fromNameAddress,
                "12345");

        // create To Header
        SipURI toAddress = addressFactory.createSipURI(toUser, toSipAddress);
        Address toNameAddress = addressFactory.createAddress(toAddress);
        toNameAddress.setDisplayName(toDisplayName);
        ToHeader toHeader = headerFactory.createToHeader(toNameAddress, null);

        // create Request URI
        SipURI requestURI = addressFactory.createSipURI(toUser, peerHostPort);

        // Create ViaHeaders
        ArrayList<ViaHeader> viaHeaders = new ArrayList<ViaHeader>();
        ViaHeader viaHeader = headerFactory.createViaHeader(localHost,
                sipProvider.getListeningPoint(transport).getPort(), transport,
                null);
        // add via headers
        viaHeaders.add(viaHeader);

        // Create ContentTypeHeader
        ContentTypeHeader contentTypeHeader = headerFactory
                .createContentTypeHeader("application", "sdp");

        // Create a new CallId header
        CallIdHeader callIdHeader;
        callIdHeader = sipProvider.getNewCallId();
        if (callId.trim().length() > 0)
            callIdHeader.setCallId(callId);

        // Create a new Cseq header
        CSeqHeader cSeqHeader = headerFactory.createCSeqHeader(invco,
                Request.INVITE);

        // Create a new MaxForwardsHeader
        MaxForwardsHeader maxForwards = headerFactory
                .createMaxForwardsHeader(70);

        // Create the request.
        Request request = messageFactory.createRequest(requestURI,
                Request.INVITE, callIdHeader, cSeqHeader, fromHeader, toHeader,
                viaHeaders, maxForwards);
        // Create contact headers
        String host = localHost;

        SipURI contactUrl = addressFactory.createSipURI(fromName, host);
        contactUrl.setPort(udpListeningPoint.getPort());

        // Create the contact name address.
        SipURI contactURI = addressFactory.createSipURI(fromName, host);
        contactURI.setPort(sipProvider.getListeningPoint(transport).getPort());

        Address contactAddress = addressFactory.createAddress(contactURI);

        // Add the contact address.
        contactAddress.setDisplayName(fromName);

        contactHeader = headerFactory.createContactHeader(contactAddress);
        request.addHeader(contactHeader);

        String sdpData = "v=0\r\n"
                + "o=4855 13760799956958020 13760799956958020"
                + " IN IP4  129.6.55.78\r\n" + "s=mysession session\r\n"
                + "p=+46 8 52018010\r\n" + "c=IN IP4  129.6.55.78\r\n"
                + "t=0 0\r\n" + "m=audio 6022 RTP/AVP 0 4 18\r\n"
                + "a=rtpmap:0 PCMU/8000\r\n" + "a=rtpmap:4 G723/8000\r\n"
                + "a=rtpmap:18 G729A/8000\r\n" + "a=ptime:20\r\n";
        byte[] contents = sdpData.getBytes();

        request.setContent(contents, contentTypeHeader);

        Header callInfoHeader = headerFactory.createHeader("Call-Info",
                "<http://www.antd.nist.gov>");
        request.addHeader(callInfoHeader);

        return request;
    }

    public void doSipRequest(String targetServer, String sipMethod) {
    	this.peerHostPort = targetServer;
        SipFactory sipFactory = null;

        sipFactory = SipFactory.getInstance();
        sipFactory.setPathName("gov.nist");

        Properties properties = new Properties();
        properties.setProperty("javax.sip.OUTBOUND_PROXY", peerHostPort + "/"
                + transport);
        properties.setProperty("javax.sip.STACK_NAME", "shootistAuth");
        properties
                .setProperty("gov.nist.javax.sip.MAX_MESSAGE_SIZE", "1048576");
        properties.setProperty("gov.nist.javax.sip.DEBUG_LOG",
                "shootistAuthdebug.txt");
        properties.setProperty("gov.nist.javax.sip.SERVER_LOG",
                "shootistAuthlog.txt");
        properties.setProperty("gov.nist.javax.sip.TRACE_LEVEL", "16");
        // Drop the client connection after we are done with the transaction.
        properties.setProperty("gov.nist.javax.sip.CACHE_CLIENT_CONNECTIONS",
                "false");

        try {
            // Create SipStack object
            sipStack = sipFactory.createSipStack(properties);
            System.out.println("createSipStack " + sipStack);
        } catch (PeerUnavailableException e) {
            // could not find gov.nist.jain.protocol.ip.sip.SipStackImpl in the
            // classpath
            e.printStackTrace();
            System.err.println(e.getMessage());
            System.exit(0);
        }
        try {
            headerFactory = sipFactory.createHeaderFactory();
            addressFactory = sipFactory.createAddressFactory();
            messageFactory = sipFactory.createMessageFactory();

			udpListeningPoint = sipStack.createListeningPoint(localHost,
                    localPort, "udp");
            sipProvider = sipStack.createSipProvider(udpListeningPoint);
            SipClient listener = this;
            sipProvider.addSipListener(listener);

        } catch (PeerUnavailableException e) {
            e.printStackTrace();
            System.err.println(e.getMessage());
            System.exit(0);
        } catch (Exception e) {
            System.out.println("Creating Listener Points");
            System.out.println(e.getMessage());
            e.printStackTrace();
        }

        try {
            System.out.println("SipClient Process ");
            Request request = this.createSipRequest(RandomUtils.getRandomLetters(8)+ "@" + peerHostPort, sipMethod);
            // Create the client transaction.
            inviteTid = sipProvider.getNewClientTransaction(request);
            // send the request out.
            inviteTid.sendRequest();
            System.out
                    .println("Register with no Authorization sent:\n" + request);
            dialog = inviteTid.getDialog();

        } catch (Exception e) {
            System.err.println("Creating call createRegister()");
            System.err.println(e.getMessage());
            e.printStackTrace();
        }
    }


    public void processIOException(IOExceptionEvent exceptionEvent) {
        System.out.println("IOException happened for "
                + exceptionEvent.getHost() + " port = "
                + exceptionEvent.getPort());

    }

    public void processTransactionTerminated(
            TransactionTerminatedEvent transactionTerminatedEvent) {
        System.out.println("Transaction terminated event recieved");
    }

    public void processDialogTerminated(
            DialogTerminatedEvent dialogTerminatedEvent) {
        System.out.println("dialogTerminatedEvent");

    }

    public static void main(String args[]) {
    	String host = TARGET_SERVER;
    	String method = Request.REGISTER;
    	if(args.length > 0)
    		host = args[0];
    	if(args.length > 1) {

    		if(args[1].equals("register")) {
    			method = Request.REGISTER;
    		}
    		else if(args[1].equals("options")) {
    			method = Request.OPTIONS;

    		}
    	}
    	if(args.length > 2) {
    		localHost = args[2];
    	}
    	System.out.println("send request to  " + host + " by " + method);
        new SipClient().doSipRequest(host, method);

    }
}
