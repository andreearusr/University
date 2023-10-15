package org.example.pages;

import net.serenitybdd.core.steps.UIInteractionSteps;
import net.thucydides.core.annotations.Step;

public class NavigateActions extends UIInteractionSteps {

    @Step
    public void toTheLoginPage() {
        openPageNamed("loginForm");
    }

    @Step
    public void toTheHomePage() {
        openPageNamed("homeForm");
    }
}