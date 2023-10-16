@rem
@rem Copyright 2015 the original author or authors.
@rem
@rem Licensed under the Apache License, Version 2.0 (the "License");
@rem you may not use this file except in compliance with the License.
@rem You may obtain a copy of the License at
@rem
@rem      https://www.apache.org/licenses/LICENSE-2.0
@rem
@rem Unless required by applicable law or agreed to in writing, software
@rem distributed under the License is distributed on an "AS IS" BASIS,
@rem WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
@rem See the License for the specific language governing permissions and
@rem limitations under the License.
@rem

@if "%DEBUG%" == "" @echo off
@rem ##########################################################################
@rem
@rem  RestServices startup script for Windows
@rem
@rem ##########################################################################

@rem Set local scope for the variables with windows NT shell
if "%OS%"=="Windows_NT" setlocal

set DIRNAME=%~dp0
if "%DIRNAME%" == "" set DIRNAME=.
set APP_BASE_NAME=%~n0
set APP_HOME=%DIRNAME%..

@rem Resolve any "." and ".." in APP_HOME to make it shorter.
for %%i in ("%APP_HOME%") do set APP_HOME=%%~fi

@rem Add default JVM options here. You can also use JAVA_OPTS and REST_SERVICES_OPTS to pass JVM options to this script.
set DEFAULT_JVM_OPTS=

@rem Find java.exe
if defined JAVA_HOME goto findJavaFromJavaHome

set JAVA_EXE=java.exe
%JAVA_EXE% -version >NUL 2>&1
if "%ERRORLEVEL%" == "0" goto execute

echo.
echo ERROR: JAVA_HOME is not set and no 'java' command could be found in your PATH.
echo.
echo Please set the JAVA_HOME variable in your environment to match the
echo location of your Java installation.

goto fail

:findJavaFromJavaHome
set JAVA_HOME=%JAVA_HOME:"=%
set JAVA_EXE=%JAVA_HOME%/bin/java.exe

if exist "%JAVA_EXE%" goto execute

echo.
echo ERROR: JAVA_HOME is set to an invalid directory: %JAVA_HOME%
echo.
echo Please set the JAVA_HOME variable in your environment to match the
echo location of your Java installation.

goto fail

:execute
@rem Setup the command line

set CLASSPATH=%APP_HOME%\lib\RestServices-1.0-SNAPSHOT-plain.jar;%APP_HOME%\lib\JocPersistence-1.0-SNAPSHOT.jar;%APP_HOME%\lib\JocModel-1.0-SNAPSHOT.jar;%APP_HOME%\lib\spring-boot-starter-actuator-2.6.3.jar;%APP_HOME%\lib\spring-boot-actuator-autoconfigure-2.6.3.jar;%APP_HOME%\lib\spring-boot-starter-web-2.6.3.jar;%APP_HOME%\lib\spring-boot-starter-json-2.6.3.jar;%APP_HOME%\lib\jackson-datatype-jsr310-2.13.1.jar;%APP_HOME%\lib\jackson-datatype-jdk8-2.13.1.jar;%APP_HOME%\lib\jackson-module-parameter-names-2.13.1.jar;%APP_HOME%\lib\jackson-databind-2.13.1.jar;%APP_HOME%\lib\jackson-core-2.13.1.jar;%APP_HOME%\lib\jackson-annotations-2.13.1.jar;%APP_HOME%\lib\sqlite-jdbc-3.36.0.3.jar;%APP_HOME%\lib\hibernate-core-jakarta-5.6.7.Final.jar;%APP_HOME%\lib\hibernate-core-5.6.4.Final.jar;%APP_HOME%\lib\jaxb-runtime-2.3.5.jar;%APP_HOME%\lib\jakarta.xml.bind-api-2.3.3.jar;%APP_HOME%\lib\spring-webmvc-5.3.15.jar;%APP_HOME%\lib\spring-boot-starter-2.6.3.jar;%APP_HOME%\lib\spring-boot-autoconfigure-2.6.3.jar;%APP_HOME%\lib\spring-boot-actuator-2.6.3.jar;%APP_HOME%\lib\spring-boot-2.6.3.jar;%APP_HOME%\lib\spring-context-5.3.15.jar;%APP_HOME%\lib\micrometer-core-1.8.2.jar;%APP_HOME%\lib\spring-boot-starter-tomcat-2.6.3.jar;%APP_HOME%\lib\spring-web-5.3.15.jar;%APP_HOME%\lib\jakarta.activation-api-1.2.2.jar;%APP_HOME%\lib\txw2-2.3.5.jar;%APP_HOME%\lib\istack-commons-runtime-3.0.12.jar;%APP_HOME%\lib\jakarta.activation-1.2.2.jar;%APP_HOME%\lib\spring-aop-5.3.15.jar;%APP_HOME%\lib\spring-beans-5.3.15.jar;%APP_HOME%\lib\spring-expression-5.3.15.jar;%APP_HOME%\lib\spring-core-5.3.15.jar;%APP_HOME%\lib\hibernate-commons-annotations-5.1.2.Final.jar;%APP_HOME%\lib\jboss-logging-3.4.3.Final.jar;%APP_HOME%\lib\jakarta.persistence-api-2.2.3.jar;%APP_HOME%\lib\byte-buddy-1.11.22.jar;%APP_HOME%\lib\antlr-2.7.7.jar;%APP_HOME%\lib\jakarta.transaction-api-1.3.3.jar;%APP_HOME%\lib\jandex-2.4.2.Final.jar;%APP_HOME%\lib\classmate-1.5.1.jar;%APP_HOME%\lib\dom4j-2.1.3.jar;%APP_HOME%\lib\javax.persistence-api-2.2.jar;%APP_HOME%\lib\jboss-transaction-api_1.2_spec-1.1.1.Final.jar;%APP_HOME%\lib\jaxb-api-2.3.1.jar;%APP_HOME%\lib\javax.activation-api-1.2.0.jar;%APP_HOME%\lib\spring-boot-starter-logging-2.6.3.jar;%APP_HOME%\lib\jakarta.annotation-api-1.3.5.jar;%APP_HOME%\lib\snakeyaml-1.29.jar;%APP_HOME%\lib\HdrHistogram-2.1.12.jar;%APP_HOME%\lib\LatencyUtils-2.0.3.jar;%APP_HOME%\lib\tomcat-embed-websocket-9.0.56.jar;%APP_HOME%\lib\tomcat-embed-core-9.0.56.jar;%APP_HOME%\lib\tomcat-embed-el-9.0.56.jar;%APP_HOME%\lib\spring-jcl-5.3.15.jar;%APP_HOME%\lib\logback-classic-1.2.10.jar;%APP_HOME%\lib\log4j-to-slf4j-2.17.1.jar;%APP_HOME%\lib\jul-to-slf4j-1.7.33.jar;%APP_HOME%\lib\logback-core-1.2.10.jar;%APP_HOME%\lib\slf4j-api-1.7.33.jar;%APP_HOME%\lib\log4j-api-2.17.1.jar


@rem Execute RestServices
"%JAVA_EXE%" %DEFAULT_JVM_OPTS% %JAVA_OPTS% %REST_SERVICES_OPTS%  -classpath "%CLASSPATH%"  %*

:end
@rem End local scope for the variables with windows NT shell
if "%ERRORLEVEL%"=="0" goto mainEnd

:fail
rem Set variable REST_SERVICES_EXIT_CONSOLE if you need the _script_ return code instead of
rem the _cmd.exe /c_ return code!
if  not "" == "%REST_SERVICES_EXIT_CONSOLE%" exit 1
exit /b 1

:mainEnd
if "%OS%"=="Windows_NT" endlocal

:omega
