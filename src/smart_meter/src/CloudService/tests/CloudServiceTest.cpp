#include "gtest/gtest.h"
#include "CloudService.h"
#include "misc/ParkingEvent.h"
#include <sstream>
#include <cstdlib>
#include <curl/curl.h>


TEST (CloudServiceTest, CreateJsonTest)
{
    spark::CloudService s;
    s.init(123, "", "");
    spark::PaymentToken token("verifier", "id123");
    spark::ParkingEvent e("ABC123", "2000-01-01 12:00", 90, token);

    std::string expectedJson = "{"
                               "\"parkingAreaId\":123,"
                               "\"parkingContextType\":\"PAID\","
                               "\"parkingDurationInMinutes\":90,"
                               "\"paymentMethodInformation\":{"
                                    "\"paymentMethodType\":\"verifier\","
                                    "\"paymentReceipt\":\"id123\""
                               "},"
                               "\"registerNumber\":\"ABC123\""
                               "}";

    std::string json = s.createParkingEventJson(e);
    EXPECT_EQ(expectedJson, json);
}



TEST (CloudServiceTest, CheckConnectionTest)
{
    spark::CloudService s;
    std::string addr = "www.google.com";
    s.init(123, "", addr);

    std::string cmd = std::string("ping -c 1 ") + addr;
    int expected = system(cmd.data()) == 0;
    bool actual = s.checkConnection();

    EXPECT_EQ(expected, actual);
}



TEST (CloudServiceTest, CreatePriceRequestJsonTest)
{
    std::string expected = "{\"parkingAreaId\":123}";
    spark::CloudService s;
    std::string json = s.createPriceRequestJSON(123);
    EXPECT_EQ(expected, json);
}


TEST (CloudServiceTest, CurlCodeToResultTest)
{
    spark::CloudService s;

    EXPECT_EQ(spark::ICloudService::OK,             s.curlCodeToResult(CURLE_OK));
    EXPECT_EQ(spark::ICloudService::TIMEOUT,        s.curlCodeToResult(CURLE_COULDNT_CONNECT));
    EXPECT_EQ(spark::ICloudService::TIMEOUT,        s.curlCodeToResult(CURLE_COULDNT_RESOLVE_HOST));
    EXPECT_EQ(spark::ICloudService::TIMEOUT,        s.curlCodeToResult(CURLE_OPERATION_TIMEDOUT));
    EXPECT_EQ(spark::ICloudService::TIMEOUT,        s.curlCodeToResult(CURLE_NO_CONNECTION_AVAILABLE));
    EXPECT_EQ(spark::ICloudService::INVALID_TOKEN,  s.curlCodeToResult(CURLE_HTTP_RETURNED_ERROR));
    EXPECT_EQ(spark::ICloudService::OTHER,          s.curlCodeToResult(CURLE_HTTP_POST_ERROR));
}


TEST (CloudServiceTest, getPricePerHour){
    double expected = 1.6 ;
    spark::CloudService s;
    s.init(1022, "https://spark2-150308.firebaseio.com/parkingArea.json?orderBy=%22area_number%22&equalTo=",
           "https://spark2-150308.appspot-preview.com/api/v1.0/parkingEvent/");

    double actual = s.getPricePerHour();

    EXPECT_EQ(expected, actual);

}


TEST (CloudServiceTest, getTimeLimitInt){
    int expected = 4*60;
    spark::CloudService s;
    s.init(1022, "https://spark2-150308.firebaseio.com/parkingArea.json?orderBy=%22area_number%22&equalTo=",
           "https://spark2-150308.appspot-preview.com/api/v1.0/parkingEvent/");

    int actual = s.getTimeLimit();

    EXPECT_EQ(expected, actual);

}


TEST (CloudServiceTest, getTimeLimitFloat){
    int expected = 0.5*60;
    spark::CloudService s;
    s.init(1234, "https://spark2-150308.firebaseio.com/parkingArea.json?orderBy=%22area_number%22&equalTo=",
           "https://spark2-150308.appspot-preview.com/api/v1.0/parkingEvent/");

    int actual = s.getTimeLimit();

    EXPECT_EQ(expected, actual);

}
