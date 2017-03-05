package com.github.walterfan.checklist.service;

import com.github.walterfan.checklist.dao.BaseObject;
import com.github.walterfan.checklist.dao.UserEntity;
import com.github.walterfan.checklist.dao.UserRepository;
import com.github.walterfan.checklist.dto.Activation;
import com.github.walterfan.checklist.dto.Registration;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Optional;
import java.util.UUID;

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
        if(!userOptional.isPresent()) {
            throw new RuntimeException("email exited");
        }

        UserEntity user = new UserEntity();
        BeanUtils.copyProperties(registration, user);
        user.setEnabled(false);
        user.setActivationCode(UUID.randomUUID().toString());

        return userRepository.save(user);
    }

    public UserEntity activate(Activation activation) {
        userRepository.findByEmail(activation.getEmail());

        UserEntity user = new UserEntity();
        BeanUtils.copyProperties(activation, user);
        user.setEnabled(false);
        user.setActivationCode(UUID.randomUUID().toString());

        return userRepository.save(user);
    }
}
