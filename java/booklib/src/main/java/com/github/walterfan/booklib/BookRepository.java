package com.github.walterfan.booklib;

/**
 * Created by yafan on 25/6/2017.
 */
import java.util.List;
import org.springframework.data.jpa.repository.JpaRepository;

public interface BookRepository extends JpaRepository<Book, Long> {

    List<Book> findByReader(String reader);

}