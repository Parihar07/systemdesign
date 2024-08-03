package com.cbr.productservice.controller;

import com.cbr.productservice.models.Product;
import com.cbr.productservice.services.ProductService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;

import java.util.ArrayList;
import java.util.List;

@RestController
@RequestMapping("/products")
public class ProductController {

    private ProductService productService;

    @Autowired
    public ProductController(ProductService productService) {
        this.productService = productService;
    }

    @GetMapping()
    public List<Product> getAllProducts() {
        return new ArrayList<>();
    }

    @GetMapping("/{id}")
    public Product getSingleProduct(@PathVariable("id") Long id) {
        return productService.getSingleProduct(id);
    }

    @PostMapping()
    public Product addNewProduct(@RequestBody Product product) {
        Product p =  new Product();
        p.setTitle("ZingoBall");
        return new Product();
    }


    @PatchMapping("/{id}")
    public Product updateProduct(@PathVariable("id") Long id, @RequestBody Product product) {
        return new Product();
    }

    @PutMapping("/{id}")
    public Product replaceProduct(@PathVariable("id") Long id, @RequestBody Product product)
    {
        return new Product();
    }

    @DeleteMapping("/{id}")
    public Product deleteProduct(@PathVariable("id") Long Id)
    {
        return new Product();
    }

}
