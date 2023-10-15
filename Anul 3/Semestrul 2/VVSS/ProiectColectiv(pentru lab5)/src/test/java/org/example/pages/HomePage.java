package org.example.pages;

import net.serenitybdd.core.annotations.findby.FindBy;
import net.serenitybdd.core.pages.PageObject;
import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.Step;

public class HomePage extends PageObject {

    @FindBy(id = "1")
    WebElementFacade product;


    @Step("Click Product")
    public void clickProduct() {
        product.click();
    }


}