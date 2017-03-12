package com.github.walterfan.checklist.dao;

import com.github.walterfan.checklist.domain.TokenType;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.OneToOne;
import javax.persistence.Table;
import java.util.Date;
import java.util.UUID;

/**
 * Created by walter on 12/03/2017.
 */
@Entity
@Table(name = "token")
public class TokenEntity extends BaseObject {

    private static final long FIVE_MINUTES_MILLI_SECONDS = 5 * 60 * 1000;

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "token_id")
    private Long id;

    @Column(name = "token_type")
    private TokenType type;

    @Column(name = "token_value")
    private String tokenValue;

    @OneToOne(targetEntity = UserEntity.class, fetch = FetchType.EAGER)
    @JoinColumn(nullable = false, name = "user_id")
    private UserEntity user;

    @Column(name = "token_value")
    private Date expiryTime;


    @Column(name = "create_time")
    private Date createTime;

    @Column(name = "last_modified_time")
    private Date lastModifiedTime;

    public void generateToken() {
        this.tokenValue = UUID.randomUUID().toString();
        this.expiryTime = calculateExpiryTime(FIVE_MINUTES_MILLI_SECONDS);
    }

    public Date calculateExpiryTime() {
        return new Date(System.currentTimeMillis() + FIVE_MINUTES_MILLI_SECONDS);
    }

    public Date calculateExpiryTime(long timeoutMilliSeconds) {
        return new Date(System.currentTimeMillis() + timeoutMilliSeconds);
    }

    public boolean isExpired() {
        return System.currentTimeMillis() - expiryTime.getTime() > 0;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public TokenType getType() {
        return type;
    }

    public void setType(TokenType type) {
        this.type = type;
    }

    public String getTokenValue() {
        return tokenValue;
    }

    public void setTokenValue(String tokenValue) {
        this.tokenValue = tokenValue;
    }

    public UserEntity getUser() {
        return user;
    }

    public void setUser(UserEntity user) {
        this.user = user;
    }

    public Date getExpiryTime() {
        return expiryTime;
    }

    public void setExpiryTime(Date expiryTime) {
        this.expiryTime = expiryTime;
    }

    public void setExpiryTime() {
        this.expiryTime = this.calculateExpiryTime();
    }

    public Date getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Date createTime) {
        this.createTime = createTime;
    }

    public Date getLastModifiedTime() {
        return lastModifiedTime;
    }

    public void setLastModifiedTime(Date lastModifiedTime) {
        this.lastModifiedTime = lastModifiedTime;
    }
}
