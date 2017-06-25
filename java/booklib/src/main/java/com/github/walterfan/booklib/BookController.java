package com.github.walterfan.booklib;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;

@Controller
@RequestMapping("/books")
public class BookController {
    private static final String reader = "walter";

    private BookRepository bookRepository;

    @Autowired
    public BookController(BookRepository bookRepository) {
        this.bookRepository = bookRepository;
    }

    @RequestMapping(method= RequestMethod.GET)
    public String readersBooks(Model model) {

        List<Book> readingList = bookRepository.findByReader(reader);
        if (readingList != null) {
            model.addAttribute("books", readingList);
        }
        return "index";
    }

    @RequestMapping(method=RequestMethod.POST)
    public String addToReadingList(Book book) {
        book.setReader(reader);
        bookRepository.save(book);
        return "redirect:/books";
    }
}

