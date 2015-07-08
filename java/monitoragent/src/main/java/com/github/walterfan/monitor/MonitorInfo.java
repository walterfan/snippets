package com.github.walterfan.monitor;

/** 
 * information holder of monitor module 
 * 
 * @version 1.0 2 June 2008 
 * @author Walter Fan Ya Min 
 */
import java.util.HashMap;
import java.util.Map;


/**
 * The Class MonitorInfo.
 */
public class MonitorInfo {
    
    /** The content type. */
    private String contentType = "";
    
    /** The content. */
    private String content = "";
    
    /** The map info. */
    private final Map<String, Object> mapInfo;

    /**
     * Instantiates a new monitor info.
     */
    public MonitorInfo() {
        this.mapInfo = new HashMap<String, Object>();
    }

    /**
     * Put info.
     *
     * @param key the key
     * @param val the val
     */
    public void putInfo(String key, Object val) {
        this.mapInfo.put(key, val);
    }

    /**
     * Gets the info.
     *
     * @param key the key
     * @return the info
     */
    public Object getInfo(String key) {
        return this.mapInfo.get(key);
    }

    /**
     * Gets the map info.
     *
     * @return the map info
     */
    public Map<String, Object> getMapInfo() {
        return this.mapInfo;
    }

    /**
     * @return String
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("");
        for (Map.Entry<String, Object> entry : mapInfo.entrySet()) {
            sb.append(entry.getKey() + " = " + entry.getValue() + "\n");
        }
        if (content != null && !content.isEmpty()) {
            sb.append("contentType=" + contentType + "\n");
            sb.append("content=" + content + "\n");
        }
        return sb.toString();
    }

    /**
     * To html string.
     *
     * @return the string
     */
    public String toHtmlString() {
        StringBuilder sb = new StringBuilder("");
        sb.append("<ul>\n");
        for (Map.Entry<String, Object> entry : mapInfo.entrySet()) {
            sb.append("<li>" + entry.getKey());
            sb.append(": " + entry.getValue() + "</li>\n");
        }
        if (content != null && !content.isEmpty()) {
            sb.append("<li>contentType=" + contentType + "</li>\n");
            sb.append("<li>content=" + content + "</li>\n");
        }
        sb.append("</ul>");
        return sb.toString();
    }

    /**
     * Gets the content.
     *
     * @return the content
     */
    public String getContent() {
        return content;
    }

    /**
     * Sets the content.
     *
     * @param content the content to set
     */
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * Gets the content type.
     *
     * @return the contentType
     */
    public String getContentType() {
        return contentType;
    }

    /**
     * Sets the content type.
     *
     * @param contentType the contentType to set
     */
    public void setContentType(String contentType) {
        this.contentType = contentType;
    }

}
