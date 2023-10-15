package org.example.pages;

import net.serenitybdd.core.annotations.findby.FindBy;
import net.serenitybdd.core.pages.PageObject;
import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.Step;

public class StepLoginPage extends PageObject {

    @FindBy(id = "email")
    WebElementFacade txtEmail;

    @FindBy(id = "password")
    WebElementFacade txtPassword;

    @FindBy(id = "login-submit")
    WebElementFacade submitButton;

    @FindBy(id = "errorM")
    WebElementFacade errorMessage;

    @Step("Enter email")
    public void inputEmail(String email) {
        txtEmail.sendKeys((email));
    }

    @Step("Enter Password")
    public void inputPassword(String passWord) {
        txtPassword.sendKeys((passWord));
    }

    @Step("Click Submit Button")
    public void clickLogin() {
        submitButton.click();
    }

    @Step("Error Message on unsuccessful login")
    public String loginPageErrorMessage() {
        return errorMessage.getText();
    }


}