package com.github.walterfan.files;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.HttpMediaTypeNotAcceptableException;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestPart;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.io.IOException;


import static javax.servlet.http.HttpServletResponse.SC_BAD_REQUEST;
import static org.springframework.web.bind.annotation.RequestMethod.POST;

@RestController
@RequestMapping("/api/v1/files")
public class FileController  {
    private static final Logger log = LoggerFactory.getLogger(FileController.class);
    @RequestMapping(method = POST, consumes = {"multipart/form-data"})
    @ResponseBody
    public ResponseEntity<String> createMediafile(@RequestPart(value = "name") String filename,
                                                  @RequestPart("file") MultipartFile file,
                                                  HttpServletRequest request , HttpServletResponse response) {

        if(file.isEmpty()){
            log.error("Empty file in request :" + filename);

        }
        byte[] fileData = null;
        try {
            fileData = file.getBytes();
            log.info("file length=" + fileData.length);
            return new ResponseEntity<String>(String.format("{\"filename\":\"%s\"}",filename), HttpStatus.OK);
        } catch (IOException e) {
            log.error("Error reading file content:" + filename, e);

        }
        return new ResponseEntity<String>(String.format("{\"filename\":\"%s\"}",filename), HttpStatus.BAD_REQUEST);
    }

}