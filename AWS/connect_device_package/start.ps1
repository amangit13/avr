# requires: Java, Maven, PowerShell, Permission to run PS scripts
# permissions for this PS session only:   Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process

# exit if cmdlet gives error
$ErrorActionPreference = "Stop"

# Check to see if root CA file exists, download if not
If (!(Test-Path ".\root-CA.crt")) {
    "`nDownloading AWS IoT Root CA certificate from AWS..."
    Invoke-WebRequest -Uri https://www.amazontrust.com/repository/AmazonRootCA1.pem -OutFile root-CA.crt
}

If (!(Test-Path ".\aws-iot-device-sdk-java")) {
    "`nInstalling AWS SDK..."
    git clone https://github.com/aws/aws-iot-device-sdk-java.git
    cd aws-iot-device-sdk-java
    mvn install --% -Dgpg.skip=true
    cd ..
}

"`nRunning the pub/sub sample application..."
cd aws-iot-device-sdk-java
mvn exec:java -pl aws-iot-device-sdk-java-samples --% -Dexec.mainClass="com.amazonaws.services.iot.client.sample.pubSub.PublishSubscribeSample" -Dexec.args="-clientEndpoint a23qaif9ryeht1-ats.iot.us-west-2.amazonaws.com -clientId sdk-java -certificateFile ..\plug.cert.pem -privateKeyFile ..\plug.private.key"
