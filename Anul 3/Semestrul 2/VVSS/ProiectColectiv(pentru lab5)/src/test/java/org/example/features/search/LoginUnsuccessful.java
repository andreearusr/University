package org.example.features.search;

import static org.assertj.core.api.Assertions.assertThat;
import net.serenitybdd.core.Serenity;
import net.serenitybdd.junit.runners.SerenityParameterizedRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import net.thucydides.core.annotations.Title;
import net.thucydides.junit.annotations.Qualifier;
import net.thucydides.junit.annotations.TestData;
import net.thucydides.junit.annotations.UseTestDataFrom;
import org.example.pages.NavigateActions;
import org.example.pages.StepLoginPage;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

import java.util.ArrayList;


@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom(value = "testdata/data.csv")
public class LoginUnsuccessful {

    @Managed
    public WebDriver driver;

    private String email, password, errorMessage;

    @Steps
    NavigateActions navigate;

    @Steps
    StepLoginPage loginPage;

    @TestData(columnNames = "Email, Password, ErrorMessage")


    @Qualifier
    public String qualifier(){return " - " + " Email = " + email + " and " + " Password = " + password + " should display " + errorMessage;}


    @Test
    @Title("Login to application with invalid credential generates error message")
    public void unsuccessfulLogin() {

        // Given
        navigate.toTheLoginPage();

        // When
        loginPage.inputEmail(email);
        loginPage.inputPassword(password);
        loginPage.clickLogin();

        // Then
        Serenity.reportThat("Passing invalid credentials generates error message",
                () -> assertThat(loginPage.loginPageErrorMessage()).isEqualToIgnoringCase("Wrong username or password!"));
    }



}
