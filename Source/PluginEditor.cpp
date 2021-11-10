/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A1AudioProcessorEditor::A1AudioProcessorEditor (A1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    // Below the slider style, range, starting value, text box and label are set and made visible.
    // Listeners are also added to track changes to parameters
    
    
    
    mGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    addAndMakeVisible(mGainSlider);
    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.vt, "GAIN", mGainSlider);
    mGainSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, mGainSlider.getTextBoxHeight());
    mGainLabel.setText("Gain", juce::dontSendNotification);
    addAndMakeVisible(mGainLabel);
    mGainLabel.attachToComponent(&mGainSlider, false);
    
    mKSigLevel1Slider.setSliderStyle(juce::Slider::LinearVertical);
    kSigLevel1SliderAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.vt, "KSIG1", mKSigLevel1Slider);
    addAndMakeVisible(mKSigLevel1Slider); // ensures it appears
    mKSigLevel1Slider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, mKSigLevel1Slider.getTextBoxHeight());
    mKSigLabel1.setText("Sig Drive", juce::dontSendNotification);
    addAndMakeVisible(mKSigLabel1);
    mKSigLabel1.attachToComponent(&mKSigLevel1Slider, false);
    
    mKSigLevel2Slider.setSliderStyle(juce::Slider::LinearVertical);
    kSigLevel2SliderAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.vt, "KSIG2", mKSigLevel2Slider);
    addAndMakeVisible(mKSigLevel2Slider); // ensures it appears
    mKSigLevel2Slider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, mKSigLevel2Slider.getTextBoxHeight());
    mKSigLabel2.setText("Sig Drive", juce::dontSendNotification);
    addAndMakeVisible(mKSigLabel1);
    mKSigLabel2.attachToComponent(&mKSigLevel2Slider, false);
    
    mDSigSlider1.setSliderStyle(juce::Slider::LinearVertical);
    dSigSlider1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.vt, "DSIG1", mDSigSlider1);
    addAndMakeVisible(mDSigSlider1); // ensures it appears
    mDSigSlider1.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, mDSigSlider1.getTextBoxHeight());
    mDSigLabel.setText("Sig Blend", juce::dontSendNotification);
    addAndMakeVisible(mDSigLabel);
    mDSigLabel.attachToComponent(&mDSigSlider1, false);
    
    mDSigSlider2.setSliderStyle(juce::Slider::LinearVertical);
    dSigSlider2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.vt, "DSIG2", mDSigSlider2);
    addAndMakeVisible(mDSigSlider2); // ensures it appears
    mDSigSlider2.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, mDSigSlider2.getTextBoxHeight());
    mDSigLabel2.setText("Sig Blend", juce::dontSendNotification);
    addAndMakeVisible(mDSigLabel2);
    mDSigLabel2.attachToComponent(&mDSigSlider2, false);
    
    mRTanSlider.setSliderStyle(juce::Slider::LinearVertical);
    rTanSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.vt, "RTAN", mRTanSlider);
    addAndMakeVisible(mRTanSlider);
    mRTanSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, mRTanSlider.getTextBoxHeight());
    mRTanLabel.setText("Tan Drive", juce::dontSendNotification);
    addAndMakeVisible(mRTanLabel);
    mRTanLabel.attachToComponent(&mRTanSlider, false);
    
    mDTanSlider.setSliderStyle(juce::Slider::LinearVertical);
    dTanSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.vt, "DTAN", mDTanSlider);
    addAndMakeVisible(mDTanSlider);
    mDTanSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, mDTanSlider.getTextBoxHeight());
    mDTanLabel.setText("Tan Blend", juce::dontSendNotification);
    addAndMakeVisible(mDTanLabel);
    mDTanLabel.attachToComponent(&mDTanSlider, false);
    
    mWDSlider.setSliderStyle(juce::Slider::LinearVertical);
    wDSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.vt, "WD", mWDSlider);
    addAndMakeVisible(mWDSlider);
    mWDSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, mWDSlider.getTextBoxHeight());
    mWDLabel.setText("Wet/Dry", juce::dontSendNotification);
    addAndMakeVisible(mWDLabel);
    mWDLabel.attachToComponent(&mWDSlider, false);
    
    mCasParMixSlider.setSliderStyle(juce::Slider::LinearVertical);
    casParMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.vt, "CASPARMIX", mCasParMixSlider);
    addAndMakeVisible(mCasParMixSlider);
    mCasParMixSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, mCasParMixSlider.getTextBoxHeight());
    mCasParMixLabel.setText("Cascade/Parallel Blend", juce::dontSendNotification);
    addAndMakeVisible(mCasParMixLabel);
    mCasParMixLabel.attachToComponent(&mCasParMixSlider, false);
    
    mFGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    fGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.vt, "FGAIN", mFGainSlider);
    addAndMakeVisible(mFGainSlider);
    mFGainSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, mFGainSlider.getTextBoxHeight());
    mFGainLabel.setText("Out Gain", juce::dontSendNotification);
    addAndMakeVisible(mFGainLabel);
    mFGainLabel.attachToComponent(&mFGainSlider, false);
    
    
    // The button parameters
    mParallelButton.setButtonText("Parallel On");
    mParallelButton.addListener(this);
    addAndMakeVisible(mParallelButton);
    
 
    // The size of the plugin in pixels
    setSize(600, 600);
}

A1AudioProcessorEditor::~A1AudioProcessorEditor()
{
}

//==============================================================================
void A1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

   
    
}

void A1AudioProcessorEditor::resized()
{
    
    // Here the dimensions of the slider are set as well as positioned on the slider.
    mGainSlider.setBounds(40, 50, 60, 200);
    mKSigLevel1Slider.setBounds(120, 50, 60, 200);
    mDSigSlider1.setBounds(200, 50, 60, 200);
    mRTanSlider.setBounds(280, 50, 60, 200);
    mDTanSlider.setBounds(360, 50, 60, 200);
    mWDSlider.setBounds(440, 50, 60, 200);
    mFGainSlider.setBounds(520, 50, 60, 200);
    
    mParallelButton.setBounds(40, 300, 60, 60);
    mKSigLevel2Slider.setBounds(120, 300, 60, 200);
    mDSigSlider2.setBounds(200, 300, 60, 200);
    mCasParMixSlider.setBounds(280, 300, 60, 200);
}

void A1AudioProcessorEditor::sliderValueChanged(juce::Slider *slider)

// This overridden function conects the interface and the process block.
// By taken the member varialbes of the processheader and assigning them to the value of each slider
// using the getValue functions ensures that all user movements to parameters effect the exectution
// in the process block.


{
    
}


void A1AudioProcessorEditor::buttonClicked(juce::Button* button)
// Again, using the same method as in the slider 

{
    if (button == &mParallelButton){
        audioProcessor.mParallelOn = mParallelButton.getToggleState();
    }
 
}
