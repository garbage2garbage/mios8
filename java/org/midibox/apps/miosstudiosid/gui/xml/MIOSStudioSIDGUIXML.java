package org.midibox.apps.miosstudiosid.gui.xml;

import org.midibox.apps.miosstudio.gui.xml.MIOSStudioGUIXML;
import org.midibox.apps.miosstudiosid.MIOSStudioSID;
import org.midibox.apps.miosstudiosid.gui.MIOSStudioSIDGUI;

public class MIOSStudioSIDGUIXML extends MIOSStudioGUIXML {

	public MIOSStudioSIDGUIXML(MIOSStudioSID miosStudioSID,
			String rootElementTag, boolean includeModel, boolean includeGUI,
			boolean includeExternalCommands, boolean includeLookAndFeel,
			boolean includeMRU) {
		super(miosStudioSID, rootElementTag, includeModel, includeGUI,
				includeExternalCommands, includeLookAndFeel, includeMRU);
	}

	public MIOSStudioSIDGUIXML(MIOSStudioSIDGUI miosStudioSIDGUI,
			String rootElementTag, boolean includeModel, boolean includeGUI,
			boolean includeExternalCommands, boolean includeLookAndFeel,
			boolean includeMRU) {
		super(miosStudioSIDGUI, rootElementTag, includeModel, includeGUI,
				includeExternalCommands, includeLookAndFeel, includeMRU);
	}

	protected MIOSStudioSIDGUIXML(MIOSStudioSIDGUI miosStudioSIDGUI,
			MIOSStudioSID miosStudioSID, String rootElementTag,
			boolean includeModel, boolean includeGUI,
			boolean includeExternalCommands, boolean includeLookAndFeel,
			boolean includeMRU) {
		super(miosStudioSIDGUI, miosStudioSID, rootElementTag, includeModel,
				includeGUI, includeExternalCommands, includeLookAndFeel,
				includeMRU);
	}

	protected void createGUI() {

		this.miosStudioGUI = new MIOSStudioSIDGUI((MIOSStudioSID) miosStudio);
	}
}
