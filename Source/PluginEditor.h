/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class A1AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener, public juce::Button::Listener


{
public:
    A1AudioProcessorEditor (A1AudioProcessor&);
    ~A1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    // Ovdfiding functions in the listener class to create
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    
    
    // Slider objects
    juce::Slider mGainSlider;
    juce::Slider mKSigLevel1Slider;
    juce::Slider mKSigLevel2Slider;
    juce::Slider mDSigSlider1;
    juce::Slider mDSigSlider2;
    juce::Slider mWDSlider;
    juce::Slider mDTanSlider;
    juce::Slider mRTanSlider;
    juce::Slider mFGainSlider;
    juce::Slider mCasParMixSlider;
 
    
    // Label objects
    juce::Label mGainLabel;
    juce::Label mKSigLabel1;
    juce::Label mKSigLabel2;
    juce::Label mDSigLabel;
    juce::Label mDSigLabel2;
    juce::Label mWDLabel;
    juce::Label mDTanLabel;
    juce::Label mRTanLabel;
    juce::Label mFGainLabel;
    juce::Label mCasParMixLabel;
    
    // Button objects
    juce::ToggleButton mParallelButton;
   
    
    //Slider value tree method - must go below the slider as it needs to be destroyed before the slider object
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> kSigLevel1SliderAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> kSigLevel2SliderAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dSigSlider1Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dSigSlider2Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wDSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dTanSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rTanSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> casParMixSliderAttachment;
    
    
    // Not creating a test audio processor but pointing to a piece of memory that already exists of the same type.
    A1AudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A1AudioProcessorEditor)
};
