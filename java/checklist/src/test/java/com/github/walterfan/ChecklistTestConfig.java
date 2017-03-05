package com.github.walterfan;

import org.springframework.context.annotation.Configuration;
import org.springframework.http.converter.HttpMessageConverter;
import org.springframework.http.converter.json.MappingJackson2HttpMessageConverter;
import org.springframework.web.servlet.HandlerExceptionResolver;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurationSupport;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by walterfan on 27/2/2017.
 */
@Configuration
public class ChecklistTestConfig extends WebMvcConfigurationSupport {

    @Override
    public void configureHandlerExceptionResolvers(List<HandlerExceptionResolver> exceptionResolvers) {
        super.configureHandlerExceptionResolvers(exceptionResolvers);
        //exceptionResolvers.add(0, new ExceptionResolver());
    }

    @Override
    public void configureMessageConverters(List<HttpMessageConverter<?>> converters) {
        super.configureMessageConverters(converters);
        if (converters == null) converters = new ArrayList<>();
        // we know we should be user fasterxml but we're not ready yet
        MappingJackson2HttpMessageConverter conv = new MappingJackson2HttpMessageConverter();
        // This ObjectMapper is properly configured, including date formatting.
        //conv.setObjectMapper(JsonUtil.getObjectMapper());
        converters.add(0, conv);
    }

}
