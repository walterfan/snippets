package com.github.walterfan.userservice;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.UUID;

@RestController
@RequestMapping("/users")
public class UserController {
    @Autowired
    private UserDetailService userDetailService;

    @RequestMapping(method= RequestMethod.POST)
    public ResponseEntity<UserDetail> createUser(@RequestBody UserDetail userDetail) {
        if(userDetail.getUserId() == null) {
            userDetail.setUserId(UUID.randomUUID().toString());
        }
        return new ResponseEntity<UserDetail>(userDetail, HttpStatus.CREATED);
    }

    @RequestMapping(method= RequestMethod.GET, value="{userId}")
    public ResponseEntity<UserDetail> getUser(@PathVariable UUID userId) {
        UserDetail userDetail = userDetailService.getUser(userId);
        if(userDetail == null) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        return new ResponseEntity<>(userDetail, HttpStatus.CREATED);
    }

    @RequestMapping(method= RequestMethod.DELETE, value="{userId}")
    public ResponseEntity<String> deleteUser(@PathVariable UUID userId) {
        UserDetail userDetail = userDetailService.getUser(userId);
        if(userDetail == null) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        this.userDetailService.deleteUser(userId);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
}
