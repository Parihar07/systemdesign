package com.cbr.productservice.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/hello")
public class HelloController {
    @GetMapping("/say/{name}/{times}")
    public String sayHello(@PathVariable("name") String name,
                           @PathVariable("times") int times)
    {
        String result = "";
        System.out.println("Hello World");
        for(int i=0;i<=times;i++)
        {
            result += "Hello " + name + "!<br>";
        }
        return result;
    }
}
