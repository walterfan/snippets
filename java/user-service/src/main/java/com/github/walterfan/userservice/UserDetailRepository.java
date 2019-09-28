package com.github.walterfan.userservice;

import org.springframework.data.jpa.repository.JpaRepository;

public interface UserDetailRepository  extends JpaRepository<UserDetail, Integer> {
    UserDetail findByUserId(String userId);
}
