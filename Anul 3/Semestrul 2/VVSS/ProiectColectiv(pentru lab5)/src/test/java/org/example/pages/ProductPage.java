package org.example.pages;

import net.serenitybdd.core.annotations.findby.FindBy;
import net.serenitybdd.core.pages.PageObject;
import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.Step;

public class ProductPage extends PageObject {

    @FindBy(id = "addToCart")
    WebElementFacade addToCart;

    @FindBy(id = "logout")
    WebElementFacade logout;


    @Step("Click Add To Cart")
    public WebElementFacade clickAddToCart() {
        addToCart.click();
        return addToCart;
    }

    @Step("Click Logout")
    public void clickLogout() {
        logout.click();
    }

}
