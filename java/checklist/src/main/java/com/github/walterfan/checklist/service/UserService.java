package com.github.walterfan.checklist.service;

import com.github.walterfan.checklist.dao.BaseObject;
import com.github.walterfan.checklist.dao.TokenEntity;
import com.github.walterfan.checklist.dao.UserEntity;
import com.github.walterfan.checklist.dao.UserRepository;
import com.github.walterfan.checklist.domain.UserStatus;
import com.github.walterfan.checklist.dto.Activation;
import com.github.walterfan.checklist.dto.Registration;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.Optional;

/**
 * Created by walterfan on 7/2/2017.
 */
@Service
public class UserService extends BaseObject {
    public static final int ACTIVATION_CODE_SIZE = 32;
    @Autowired
    private UserRepository userRepository;

    public UserEntity register(Registration registration) {

        Optional<UserEntity> userOptional = userRepository.findByEmail(registration.getEmail());
        if(userOptional.isPresent()) {
            throw new RuntimeException("The email existed: " + registration.getEmail());
        }

        UserEntity user = new UserEntity();
        BeanUtils.copyProperties(registration, user);
        TokenEntity token = new TokenEntity();
        token.generateToken();
        user.setTokens(Arrays.asList(token));

        return userRepository.save(user);
    }

    public UserEntity activate(Activation activation) {
        userRepository.findByEmail(activation.getEmail());

        UserEntity user = new UserEntity();
        BeanUtils.copyProperties(activation, user);
        user.setStatus(UserStatus.active);

        return userRepository.save(user);
    }
}
