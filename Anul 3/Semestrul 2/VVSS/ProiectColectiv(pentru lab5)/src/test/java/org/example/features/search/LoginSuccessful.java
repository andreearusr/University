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


@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom(value = "testdata/dataSuccess.csv")
public class LoginSuccessful {

    @Managed
    public WebDriver driver;

    private String email, password, errorMessage;

    @Steps
    NavigateActions navigate;

    @Steps
    StepLoginPage loginPage;

    @TestData(columnNames = "Email, Password, ErrorMessage")


    @Qualifier
    public String qualifier() {
        return " - " + " Email = " + email + " and " + " Password = " + password + " should display " + errorMessage;
    }

    @Test
    @Title("Login to application with valid credential generates no error message")
    public void successfulLogin() {

        // Given
        navigate.toTheLoginPage();

        // When
        loginPage.inputEmail(email);
        loginPage.inputPassword(password);
        loginPage.clickLogin();

        // Then
        Serenity.reportThat("Passing valid credentials navigates to HomePage",
                () -> assertThat(driver.getCurrentUrl()).isEqualTo("http://127.0.0.1:3000/products"));
    }

}