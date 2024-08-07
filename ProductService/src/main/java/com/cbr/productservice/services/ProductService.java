package com.cbr.productservice.services;

import com.cbr.productservice.models.Product;

import java.util.List;

public interface ProductService {
    Product getSingleProduct(Long id);
    List<Product> getAllProducts();
    Product replaceProduct(Long id, Product product);
    Product updateProduct(Long id, Product product);
    Product deleteProduct(Long id);
    Product addProduct(Product product);
}
