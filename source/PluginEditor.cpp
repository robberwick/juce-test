#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    // addAndMakeVisible (inspectButton);
    //
    // // this chunk of code instantiates and opens the melatonin inspector
    // inspectButton.onClick = [&] {
    //     if (!inspector)
    //     {
    //         inspector = std::make_unique<melatonin::Inspector> (*this);
    //         inspector->onClose = [this]() { inspector.reset(); };
    //     }
    //
    //     inspector->setVisible (true);
    // };

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 400);
    setResizable (true, true);

    addAndMakeVisible (gainslider);
    gainslider.setSliderStyle (juce::Slider::LinearVertical);
    gainslider.setRange (-48.0, 0.0);
    gainslider.setValue (-1.0);
    gainslider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100,20);
    gainslider.addListener (this);
}

PluginEditor::~PluginEditor()
{
}

void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


}

void PluginEditor::resized()
{
    // layout the positions of your child components here
    auto area = getLocalBounds();
    // area.removeFromBottom(50);
    // inspectButton.setBounds (getLocalBounds().withSizeKeepingCentre(100, 50));
    gainslider.setBounds (getLocalBounds());
}

void PluginEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &gainslider)
    {
        processorRef.rawGainValue = pow(10, gainslider.getValue() / 20);
    }

}
