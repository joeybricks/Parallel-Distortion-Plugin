/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::AudioProcessorValueTreeState::ParameterLayout A1AudioProcessor::createParameterLayout()
{
    
}

//==============================================================================
//Constructor for 'A1AudioProcessor' must explicitly initialize the member 'treeState' which does not have a default constructor
A1AudioProcessor::A1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       
                       // this is de referenced as it is a pointer to the instantiation of the class we are in
                       ), vt(*this, nullptr, "Parameters", createParameters())

// Initialiser list - for constructors that need to be initialised instantly
#endif
{
}

A1AudioProcessor::~A1AudioProcessor()
{
}

//==============================================================================
const juce::String A1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool A1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool A1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool A1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double A1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int A1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int A1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void A1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String A1AudioProcessor::getProgramName (int index)
{
    return {};
}

void A1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void A1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void A1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool A1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void A1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // All processing of audio data will take place within this function.
    
    // Find lenght of buffer
    int numSamples = buffer.getNumSamples();
    if (numSamples == 0){
        return;
    }
    int numChannels = buffer.getNumChannels();
    int outputChannels = getTotalNumOutputChannels();
    
    
    // Find wrtie output pointers and initiate them both to 0.
    auto channelDataL = buffer.getWritePointer(0);
    auto channelDataR = buffer.getWritePointer(0);
    // If a second channel is detected, it will reassign channelDataR to 1.
    if (numChannels == 2){
        channelDataR = buffer.getWritePointer(1);
    }
    
    // Set up storage for input samples
    float input = 0.0f;
    
    auto gain = vt.getRawParameterValue("GAIN");
    auto ksig1 = vt.getRawParameterValue("KSIG1");
    auto ksig2 = vt.getRawParameterValue("KSIG2");
    auto dsig1 = vt.getRawParameterValue("DSIG1");
    auto dsig2 = vt.getRawParameterValue("DSIG2");
    auto wd = vt.getRawParameterValue("WD");
    auto rtan = vt.getRawParameterValue("RTAN");
    auto dtan = vt.getRawParameterValue("DTAN");
    auto casparmix = vt.getRawParameterValue("CASPARMIX");
    auto fgain = vt.getRawParameterValue("FGAIN");
    
    // begin main time loop
    for (int n = 0; n < numSamples; n++){
        input = buffer.getSample(0,n);
         
        
        // Decleration of variables of type float that will be used to blend multiple signals.
        float wet = 1-wd->load(), tBlend = 1-dtan->load(), sBlend = 1-dsig1->load(), sBlend2 = 1-dsig2->load(), CasParBLend = 1-casparmix->load();
      

        // Applying the sigmloid and hyperbolic tangent algorithms in cascade.
        channelDataL[n] = (wd->load()*(input*gain->load()))+ (wet * ((dsig1->load() * (gain->load()*input)) + (sBlend * ((1/atanf(ksig1->load())) * atanf(ksig1->load() * gain->load()*input)))));
        auto temp = (wd->load() * (gain->load() * channelDataL[n])) + (wet*(((dtan->load() * (channelDataL[n] * gain->load() * rtan->load())) + (tBlend * tanhf(gain->load() * channelDataL[n]*rtan->load())))));
        channelDataL[n] = temp;
    
       
      
        // Linked to the toggle button, if the button is pressed the programe will implement the parralel section
        if (mParallelOn == true){
            temp = (wd->load()*(input*gain->load()))+ (wet * ((dsig2->load() * (gain->load()*input)) + (sBlend2 * ((1/atanf(ksig2->load())) * atanf(ksig2->load() * gain->load()*input)))));
            
            // Blending the parallel and cascaded signals
        channelDataL[n] = casparmix->load()*channelDataL[n] + CasParBLend*temp;
    }
         // Final gain stage
        channelDataL[n] = fgain->load()*channelDataL[n];
        
        
        
        
        // Implementing 'big mono'
        if (outputChannels == 2){
            channelDataR[n] = channelDataL[n];
        }
    
    }
}

//==============================================================================
bool A1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}


juce::AudioProcessorEditor* A1AudioProcessor::createEditor()
{
    
//    return new A1AudioProcessorEditor(*this);
    return new foleys::MagicPluginEditor (magicState);//    return new A1AudioProcessorEditor (*this);
}

//==============================================================================
void A1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream(destData, true);
    
}

void A1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new A1AudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout A1AudioProcessor::createParameters()
{
// Vector that will return parameter layout
    // effectively pointers of ranged audio paramters, contained in a vector or a list.
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    
    // adding element to the end of the vector using the pushback method
    // This unique pointer needs memory alocated, this is done via make_unique and initialising the AudioParameterFloat
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("KSIG1", "Ksig1", 1.0f, 7.0f, 3.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("KSIG2", "Ksig1", 1.0f, 7.0f, 3.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DSIG1", "Dsig1", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DSIG2", "Dsig1", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RTAN", "Rtan", 1.0f, 7.0f, 3.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DTAN", "Dtan", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WD", "Wd", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CASPARMIX", "CasParMix", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FGAIN", "Fgain", 0.0f, 1.0f, 0.5f));
    
    
    
    // returns the vector
    return {params.begin(), params.end()};
    
    
}

