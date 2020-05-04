// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "firebending_trials.h"

using cinder::app::App;
using cinder::app::RendererGl;

namespace trials {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  settings->setFrameRate(60.0f);
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("Avatar : Firebending Trials");
}

}  // namespace trials

// This is a macro that runs the application.
CINDER_APP(trials::MyApp,
           RendererGl(RendererGl::Options().msaa(trials::kSamples)),
           trials::SetUp)
