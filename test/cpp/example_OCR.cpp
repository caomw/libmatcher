/*
    This is a sample code to preset how to use Matcher library.
 */

#include <iostream>
#include "../../Matcher.hpp"
#include "../../MatchEntry.hpp"
#include "../../MatcherUtils.hpp"

std::string SCREENSHOT = "../img/appgrid.png";

void printresults(const MatchResult *mresult) {
    std::cout << "Result: " << mresult->result[0] << std::endl;
    std::cout << "bbox: " << mresult->bbox[0] << std::endl;
    std::cout << "coord: " << mresult->center[0] << std::endl;
    std::cout << "result image: " << mresult->resultimage << std::endl;
    std::cout << "message: " << mresult->message << std::endl;
}

int main() {
    // First of all we need to have Matcher configuration
    matcher::MatcherConfig mconfig;
    mconfig.useOCR = true;
    mconfig.useOIR = true;
    mconfig.nfeatures = 10000;
    mconfig.scaleFactor = 1.2f;  // for > 1.4f GPU ORB fails
    mconfig.nlevels = 10;
    mconfig.edgeThreshold = 9;
    mconfig.firstLevel = 0;
    mconfig.WTA_K = 2;
    mconfig.scoreType = 0;
    mconfig.patchSize = 19;
    mconfig.min_dist_thresh = 0;
    mconfig.max_nndr_ratio = 1;
    mconfig.ransac_reprojection_thresh = 10.0f;
    mconfig.min_inliers = 8;
    mconfig.gpu_enabled = false;
    mconfig.scale_invariant = false;
    mconfig.locate = true;

    // Now we can create Matcher object
    cv::Ptr<Matcher> matcher = new Matcher(mconfig);

    // Load screenshot and icon image
    cv::Mat image = cv::imread(SCREENSHOT);

    // Create match query
    MatchQuery mquery;
    mquery.screenshot = SCREENSHOT;
    mquery.icon = "Clockwork\nTomato";
    mquery.method = matcher::LocateMethod::OCR;
    mquery.threshold = 100;
    mquery.maxlocations = 2;

    // Match icon image with screenshot
    MatchResult *mresult = new MatchResult(mquery.maxlocations);
    cv::Ptr<cv::Mat> resultimg = matcher->match(image, mquery, mresult);

    // Save result image
    matcher->drawMatchDetails(mquery, mresult, resultimg);
    MatcherUtils::saveResultImage(resultimg, mquery, mresult, SCREENSHOT);

    // Print results
    printresults(mresult);
    delete mresult;
    return 0;
}