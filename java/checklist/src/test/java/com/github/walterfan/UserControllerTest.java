package com.github.walterfan;

import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.testng.AbstractTestNGSpringContextTests;
import org.springframework.test.context.web.WebAppConfiguration;

/**
 * Created by walterfan on 27/2/2017.
 */
@WebAppConfiguration
@ContextConfiguration(classes = {ChecklistTestConfig.class})
public class UserControllerTest extends AbstractTestNGSpringContextTests {
}
