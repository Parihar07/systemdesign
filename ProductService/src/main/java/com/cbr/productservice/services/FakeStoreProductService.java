package com.cbr.productservice.services;

import com.cbr.productservice.dto.FakeStoreProductDto;
import com.cbr.productservice.models.Category;
import com.cbr.productservice.models.Product;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;


@Service
public class FakeStoreProductService implements ProductService {

    private RestTemplate restTemplate;

    @Autowired
    public FakeStoreProductService(RestTemplate restTemplate) {
        this.restTemplate = restTemplate;
    }

    private Product convertFakeStoreProductDtoToProduct(FakeStoreProductDto fakeStoreProductDto) {
        Product product = new Product();
        product.setId(fakeStoreProductDto.getId());
        product.setTitle(fakeStoreProductDto.getTitle());
        product.setDescription(fakeStoreProductDto.getDescription());
        product.setPrice(fakeStoreProductDto.getPrice());
//        product.setCategory(new Category());
        product.setCategory(new Category());
        product.getCategory().setName(fakeStoreProductDto.getCategory());

        return product;
    }

    @Override
    public Product getSingleProduct(Long id) {
        FakeStoreProductDto fakeStoreProductDto =  restTemplate.getForObject("https://fakestoreapi.com/products/" + id, FakeStoreProductDto.class);
        // Here fakestore apu has diffrent datatype sent in return hence we need to introduce DTO
        //Convert fakestoreproduct dto to product

        return convertFakeStoreProductDtoToProduct(fakeStoreProductDto);
    }
}
