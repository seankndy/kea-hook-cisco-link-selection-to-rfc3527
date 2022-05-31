#include <hooks/hooks.h>
#include <dhcp/pkt4.h>
#include <log/logger.h>
#include <log/macros.h>
#include "utils.h"

using namespace std;
using namespace isc::dhcp;
using namespace isc::hooks;

static const uint16_t RAI_OPTION_CISCO_LINK_SELECTION = 150;

isc::log::Logger hook_logger("cisco_link_selection_to_rfc3527");

extern "C" {

    int pkt4_receive(CalloutHandle& handle) {
        Pkt4Ptr pkt4;
        handle.getArgument("query4", pkt4);

        // if no RAI, nothing to do
        auto rai = pkt4->getOption(DHO_DHCP_AGENT_OPTIONS);
        if (!rai) {
            LOG_DEBUG(hook_logger, 99, "Packet has no RAI option, doing nothing.");
            return 0;
        }

        // if already had link-selection sub-option, nothing to do
        auto linksel = rai->getOption(RAI_OPTION_LINK_SELECTION);
        if (linksel) {
            LOG_DEBUG(hook_logger, 99, "Packet already has RAI sub-option 5 (RFC3527), doing nothing.");
            return 0;
        }

        // if cisco link-selection (subop 150) then copy that to subop 5
        auto cisco_linksel = rai->getOption(RAI_OPTION_CISCO_LINK_SELECTION);
        if (cisco_linksel) {
            OptionBuffer data = cisco_linksel->getData();

            LOG_INFO(hook_logger, "Creating RAI link-selection sub-option from Cisco's link-selection sub-option (%1)").arg(dotted_quad(data));

            rai->addOption(
                Option::create(Option::V4, RAI_OPTION_LINK_SELECTION, data)
            );
        }

        return 0;
    }

}
