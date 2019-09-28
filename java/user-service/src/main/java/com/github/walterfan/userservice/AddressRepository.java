package com.github.walterfan.userservice;

import org.springframework.data.jpa.repository.JpaRepository;

public interface AddressRepository extends JpaRepository<Address, Integer> {
    Address findByUserId(String userId);
}

