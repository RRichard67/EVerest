// SPDX-License-Identifier: Apache-2.0
// Copyright 2026 Pionix GmbH and Contributors to EVerest
#include <iso15118/message/ac_der_iec_charge_loop.hpp>

#include <type_traits>

#include <iso15118/detail/variant_access.hpp>

#include <cbv2g/iso_20/iso20_AC_DER_IEC_Decoder.h>
#include <cbv2g/iso_20/iso20_AC_DER_IEC_Encoder.h>

namespace iso15118::message_20 {

template <> void convert(const datatypes::DetailedCost& in, struct iso20_ac_der_iec_DetailedCostType& out) {
    init_iso20_ac_der_iec_DetailedCostType(&out);
    convert(in.amount, out.Amount);
    convert(in.cost_per_unit, out.CostPerUnit);
}

template <> void convert(const struct iso20_ac_der_iec_DetailedCostType& in, datatypes::DetailedCost& out) {
    convert(in.Amount, out.amount);
    convert(in.CostPerUnit, out.cost_per_unit);
}

template <> void convert(const datatypes::DetailedTax& in, struct iso20_ac_der_iec_DetailedTaxType& out) {
    init_iso20_ac_der_iec_DetailedTaxType(&out);
    out.TaxRuleID = in.tax_rule_id;
    convert(in.amount, out.Amount);
}

template <> void convert(const struct iso20_ac_der_iec_DetailedTaxType& in, datatypes::DetailedTax& out) {
    out.tax_rule_id = in.TaxRuleID;
    convert(in.Amount, out.amount);
}

template <> void convert(const datatypes::Receipt& in, struct iso20_ac_der_iec_ReceiptType& out) {
    init_iso20_ac_der_iec_ReceiptType(&out);

    out.TimeAnchor = in.time_anchor;
    CPP2CB_CONVERT_IF_USED(in.energy_costs, out.EnergyCosts);
    CPP2CB_CONVERT_IF_USED(in.occupancy_costs, out.OccupancyCosts);
    CPP2CB_CONVERT_IF_USED(in.additional_service_costs, out.AdditionalServicesCosts);
    CPP2CB_CONVERT_IF_USED(in.overstay_costs, out.OverstayCosts);

    if (sizeof(out.TaxCosts.array) < in.tax_costs.size()) {
        throw std::runtime_error("tax costs array is too large");
    }
    for (std::size_t i = 0; i < in.tax_costs.size(); ++i) {
        convert(in.tax_costs[i], out.TaxCosts.array[i]);
    }
    out.TaxCosts.arrayLen = in.tax_costs.size();
}

template <> void convert(const struct iso20_ac_der_iec_ReceiptType& in, datatypes::Receipt& out) {
    out.time_anchor = in.TimeAnchor;

    CB2CPP_CONVERT_IF_USED(in.EnergyCosts, out.energy_costs);
    CB2CPP_CONVERT_IF_USED(in.OccupancyCosts, out.occupancy_costs);
    CB2CPP_CONVERT_IF_USED(in.AdditionalServicesCosts, out.additional_service_costs);
    CB2CPP_CONVERT_IF_USED(in.OverstayCosts, out.overstay_costs);

    if (in.TaxCosts.arrayLen > 10) {
        throw std::runtime_error("tax costs array is too large");
    }
    out.tax_costs.resize(in.TaxCosts.arrayLen);
    for (std::size_t i = 0; i < in.TaxCosts.arrayLen; ++i) {
        convert(in.TaxCosts.array[i], out.tax_costs[i]);
    }
}

template <typename cb_Type> void convert(const datatypes::Scheduled_AC_CLResControlMode& in, cb_Type& out) {
    CPP2CB_CONVERT_IF_USED(in.target_active_power, out.EVSETargetActivePower);
    CPP2CB_CONVERT_IF_USED(in.target_active_power_L2, out.EVSETargetActivePower_L2);
    CPP2CB_CONVERT_IF_USED(in.target_active_power_L2, out.EVSETargetActivePower_L3);

    CPP2CB_CONVERT_IF_USED(in.target_reactive_power, out.EVSETargetReactivePower);
    CPP2CB_CONVERT_IF_USED(in.target_reactive_power_L2, out.EVSETargetReactivePower_L2);
    CPP2CB_CONVERT_IF_USED(in.target_reactive_power_L2, out.EVSETargetReactivePower_L3);

    CPP2CB_CONVERT_IF_USED(in.present_active_power, out.EVSEPresentActivePower);
    CPP2CB_CONVERT_IF_USED(in.present_active_power_L2, out.EVSEPresentActivePower_L2);
    CPP2CB_CONVERT_IF_USED(in.present_active_power_L3, out.EVSEPresentActivePower_L3);
}

template <typename InType> void convert(const InType& in, datatypes::Scheduled_AC_CLResControlMode& out) {

    CB2CPP_CONVERT_IF_USED(in.EVSETargetActivePower, out.target_active_power);
    CB2CPP_CONVERT_IF_USED(in.EVSETargetActivePower_L2, out.target_active_power_L2);
    CB2CPP_CONVERT_IF_USED(in.EVSETargetActivePower_L3, out.target_active_power_L3);

    CB2CPP_CONVERT_IF_USED(in.EVSETargetReactivePower, out.target_reactive_power);
    CB2CPP_CONVERT_IF_USED(in.EVSETargetReactivePower_L2, out.target_reactive_power_L2);
    CB2CPP_CONVERT_IF_USED(in.EVSETargetReactivePower_L3, out.target_reactive_power_L3);

    CB2CPP_CONVERT_IF_USED(in.EVSEPresentActivePower, out.present_active_power);
    CB2CPP_CONVERT_IF_USED(in.EVSEPresentActivePower_L2, out.present_active_power_L2);
    CB2CPP_CONVERT_IF_USED(in.EVSEPresentActivePower_L3, out.present_active_power_L3);
}

template <>
void convert(const datatypes::BPT_Scheduled_AC_CLResControlMode& in,
             struct iso20_ac_der_iec_BPT_Scheduled_AC_CLResControlModeType& out) {
    convert(static_cast<const datatypes::Scheduled_AC_CLResControlMode&>(in), out);
}

template <>
void convert(const iso20_ac_der_iec_BPT_Scheduled_AC_CLResControlModeType& in,
             struct datatypes::BPT_Scheduled_AC_CLResControlMode& out) {
    convert(in, static_cast<datatypes::Scheduled_AC_CLResControlMode&>(out));
}

template <> void convert(const datatypes::DsoQSetpoint& in, struct iso20_ac_der_iec_DSOQSetpointType& out) {
    convert(in.dso_q_setpoint_value, out.DSOQSetpointValue);
    CPP2CB_CONVERT_IF_USED(in.dso_q_setpoint_value_L2, out.DSOQSetpointValue_L2);
    CPP2CB_CONVERT_IF_USED(in.dso_q_setpoint_value_L3, out.DSOQSetpointValue_L3);
    out.PT1ResponseReactivePower = in.pt1_response_reactive_power;
    convert(in.step_response_time_constant_reactive_power, out.StepResponseTimeConstantReactivePower);
}

template <> void convert(const struct iso20_ac_der_iec_DSOQSetpointType& in, datatypes::DsoQSetpoint& out) {
    convert(in.DSOQSetpointValue, out.dso_q_setpoint_value);
    CB2CPP_CONVERT_IF_USED(in.DSOQSetpointValue_L2, out.dso_q_setpoint_value_L2);
    CB2CPP_CONVERT_IF_USED(in.DSOQSetpointValue_L3, out.dso_q_setpoint_value_L3);
    out.pt1_response_reactive_power = in.PT1ResponseReactivePower;
    convert(in.StepResponseTimeConstantReactivePower, out.step_response_time_constant_reactive_power);
}

template <> void convert(const datatypes::DsoCosPhiSetpoint& in, struct iso20_ac_der_iec_DSOCosPhiSetpointType& out) {
    convert(in.dso_cos_phi_setpoint_value, out.DSOCosPhiSetpointValue);
    CPP2CB_CONVERT_IF_USED(in.dso_cos_phi_setpoint_value_L2, out.DSOCosPhiSetpointValue_L2);
    CPP2CB_CONVERT_IF_USED(in.dso_cos_phi_setpoint_value_L3, out.DSOCosPhiSetpointValue_L3);
    cb_convert_enum(in.excitation, out.Excitation);
    out.PT1ResponseReactivePower = in.pt1_response_reactive_power;
    convert(in.step_response_time_constant_reactive_power, out.StepResponseTimeConstantReactivePower);
}

template <> void convert(const struct iso20_ac_der_iec_DSOCosPhiSetpointType& in, datatypes::DsoCosPhiSetpoint& out) {
    convert(in.DSOCosPhiSetpointValue, out.dso_cos_phi_setpoint_value);
    CB2CPP_CONVERT_IF_USED(in.DSOCosPhiSetpointValue_L2, out.dso_cos_phi_setpoint_value_L2);
    CB2CPP_CONVERT_IF_USED(in.DSOCosPhiSetpointValue_L3, out.dso_cos_phi_setpoint_value_L3);
    cb_convert_enum(in.Excitation, out.excitation);
    out.pt1_response_reactive_power = in.PT1ResponseReactivePower;
    convert(in.StepResponseTimeConstantReactivePower, out.step_response_time_constant_reactive_power);
}

template <>
void convert(const datatypes::DER_Scheduled_AC_CLResControlMode& in,
             struct iso20_ac_der_iec_DER_Scheduled_AC_CLResControlModeType& out) {
    convert(static_cast<const datatypes::Scheduled_AC_CLResControlMode&>(in), out);

    convert(in.max_charge_power, out.EVSEMaximumChargePower);
    CPP2CB_CONVERT_IF_USED(in.max_charge_power_L2, out.EVSEMaximumChargePower_L2);
    CPP2CB_CONVERT_IF_USED(in.max_charge_power_L3, out.EVSEMaximumChargePower_L3);

    convert(in.max_discharge_power, out.EVSEMaximumDischargePower);
    CPP2CB_CONVERT_IF_USED(in.max_discharge_power_L2, out.EVSEMaximumDischargePower_L2);
    CPP2CB_CONVERT_IF_USED(in.max_discharge_power_L3, out.EVSEMaximumDischargePower_L3);

    CPP2CB_CONVERT_IF_USED(in.dso_discharge_power, out.DSOMaximumDischargePower);
    CPP2CB_CONVERT_IF_USED(in.dso_discharge_power_L2, out.DSOMaximumDischargePower_L2);
    CPP2CB_CONVERT_IF_USED(in.dso_discharge_power_L3, out.DSOMaximumDischargePower_L3);

    CPP2CB_CONVERT_IF_USED(in.dso_q_setpoint, out.DSOQSetpoint);
    CPP2CB_CONVERT_IF_USED(in.dso_cos_phi_setpoint, out.DSOCosPhiSetpoint);
}

template <>
void convert(const struct iso20_ac_der_iec_DER_Scheduled_AC_CLResControlModeType& in,
             datatypes::DER_Scheduled_AC_CLResControlMode& out) {
    convert(in, static_cast<datatypes::Scheduled_AC_CLResControlMode&>(out));

    convert(in.EVSEMaximumChargePower, out.max_charge_power);
    CB2CPP_CONVERT_IF_USED(in.EVSEMaximumChargePower_L2, out.max_charge_power_L2);
    CB2CPP_CONVERT_IF_USED(in.EVSEMaximumChargePower_L3, out.max_charge_power_L3);

    convert(in.EVSEMaximumDischargePower, out.max_discharge_power);
    CB2CPP_CONVERT_IF_USED(in.EVSEMaximumDischargePower_L2, out.max_discharge_power_L2);
    CB2CPP_CONVERT_IF_USED(in.EVSEMaximumDischargePower_L3, out.max_discharge_power_L3);

    CB2CPP_CONVERT_IF_USED(in.DSOMaximumDischargePower, out.dso_discharge_power);
    CB2CPP_CONVERT_IF_USED(in.DSOMaximumDischargePower_L2, out.dso_discharge_power_L2);
    CB2CPP_CONVERT_IF_USED(in.DSOMaximumDischargePower_L3, out.dso_discharge_power_L3);

    CB2CPP_CONVERT_IF_USED(in.DSOQSetpoint, out.dso_q_setpoint);
    CB2CPP_CONVERT_IF_USED(in.DSOCosPhiSetpoint, out.dso_cos_phi_setpoint);
}

template <typename cb_Type> void convert(const datatypes::Dynamic_CLResControlMode& in, cb_Type& out) {
    CPP2CB_ASSIGN_IF_USED(in.departure_time, out.DepartureTime);
    CPP2CB_ASSIGN_IF_USED(in.minimum_soc, out.MinimumSOC);
    CPP2CB_ASSIGN_IF_USED(in.target_soc, out.TargetSOC);
    CPP2CB_ASSIGN_IF_USED(in.ack_max_delay, out.AckMaxDelay);
}

template <typename cb_Type> void convert(const cb_Type& in, datatypes::Dynamic_CLResControlMode& out) {
    static_assert(std::is_same_v<cb_Type, iso20_ac_der_iec_Dynamic_AC_CLResControlModeType> or
                  std::is_same_v<cb_Type, iso20_ac_der_iec_BPT_Dynamic_AC_CLResControlModeType> or
                  std::is_same_v<cb_Type, iso20_ac_der_iec_DER_Dynamic_AC_CLResControlModeType>);

    CB2CPP_ASSIGN_IF_USED(in.DepartureTime, out.departure_time);
    CB2CPP_ASSIGN_IF_USED(in.MinimumSOC, out.minimum_soc);
    CB2CPP_ASSIGN_IF_USED(in.TargetSOC, out.target_soc);
    CB2CPP_ASSIGN_IF_USED(in.AckMaxDelay, out.ack_max_delay);
}

template <typename cb_Type> void convert(const datatypes::Dynamic_AC_CLResControlMode& in, cb_Type& out) {
    convert(static_cast<const datatypes::Dynamic_CLResControlMode&>(in), out);

    convert(in.target_active_power, out.EVSETargetActivePower);
    CPP2CB_CONVERT_IF_USED(in.target_active_power_L2, out.EVSETargetActivePower_L2);
    CPP2CB_CONVERT_IF_USED(in.target_active_power_L3, out.EVSETargetActivePower_L3);

    CPP2CB_CONVERT_IF_USED(in.target_reactive_power, out.EVSETargetReactivePower);
    CPP2CB_CONVERT_IF_USED(in.target_reactive_power_L2, out.EVSETargetReactivePower_L2);
    CPP2CB_CONVERT_IF_USED(in.target_reactive_power_L3, out.EVSETargetReactivePower_L3);

    CPP2CB_CONVERT_IF_USED(in.present_active_power, out.EVSEPresentActivePower);
    CPP2CB_CONVERT_IF_USED(in.present_active_power_L2, out.EVSEPresentActivePower_L2);
    CPP2CB_CONVERT_IF_USED(in.present_active_power_L3, out.EVSEPresentActivePower_L3);
}

template <typename cb_Type> void convert(const cb_Type& in, datatypes::Dynamic_AC_CLResControlMode& out) {
    convert(in, static_cast<datatypes::Dynamic_CLResControlMode&>(out));

    convert(in.EVSETargetActivePower, out.target_active_power);
    CB2CPP_CONVERT_IF_USED(in.EVSETargetActivePower_L2, out.target_active_power_L2);
    CB2CPP_CONVERT_IF_USED(in.EVSETargetActivePower_L3, out.target_active_power_L3);

    CB2CPP_CONVERT_IF_USED(in.EVSETargetReactivePower, out.target_reactive_power);
    CB2CPP_CONVERT_IF_USED(in.EVSETargetReactivePower_L2, out.target_reactive_power_L2);
    CB2CPP_CONVERT_IF_USED(in.EVSETargetReactivePower_L3, out.target_reactive_power_L3);

    CB2CPP_CONVERT_IF_USED(in.EVSEPresentActivePower, out.present_active_power);
    CB2CPP_CONVERT_IF_USED(in.EVSEPresentActivePower_L2, out.present_active_power_L2);
    CB2CPP_CONVERT_IF_USED(in.EVSEPresentActivePower_L3, out.present_active_power_L3);
}

template <>
void convert(const datatypes::BPT_Dynamic_AC_CLResControlMode& in,
             struct iso20_ac_der_iec_BPT_Dynamic_AC_CLResControlModeType& out) {
    convert(static_cast<const datatypes::Dynamic_AC_CLResControlMode&>(in), out);
}

template <>
void convert(const struct iso20_ac_der_iec_BPT_Dynamic_AC_CLResControlModeType& in,
             datatypes::BPT_Dynamic_AC_CLResControlMode& out) {
    convert(in, static_cast<datatypes::Dynamic_AC_CLResControlMode&>(out));
}

template <>
void convert(const datatypes::DER_Dynamic_AC_CLResControlMode& in,
             struct iso20_ac_der_iec_DER_Dynamic_AC_CLResControlModeType& out) {
    convert(static_cast<const datatypes::Dynamic_AC_CLResControlMode&>(in), out);

    convert(in.max_charge_power, out.EVSEMaximumChargePower);
    CPP2CB_CONVERT_IF_USED(in.max_charge_power_L2, out.EVSEMaximumChargePower_L2);
    CPP2CB_CONVERT_IF_USED(in.max_charge_power_L3, out.EVSEMaximumChargePower_L3);

    convert(in.max_discharge_power, out.EVSEMaximumDischargePower);
    CPP2CB_CONVERT_IF_USED(in.max_discharge_power_L2, out.EVSEMaximumDischargePower_L2);
    CPP2CB_CONVERT_IF_USED(in.max_discharge_power_L3, out.EVSEMaximumDischargePower_L3);

    CPP2CB_CONVERT_IF_USED(in.dso_discharge_power, out.DSOMaximumDischargePower);
    CPP2CB_CONVERT_IF_USED(in.dso_discharge_power_L2, out.DSOMaximumDischargePower_L2);
    CPP2CB_CONVERT_IF_USED(in.dso_discharge_power_L3, out.DSOMaximumDischargePower_L3);

    CPP2CB_CONVERT_IF_USED(in.dso_q_setpoint, out.DSOQSetpoint);
    CPP2CB_CONVERT_IF_USED(in.dso_cos_phi_setpoint, out.DSOCosPhiSetpoint);
}

template <>
void convert(const struct iso20_ac_der_iec_DER_Dynamic_AC_CLResControlModeType& in,
             datatypes::DER_Dynamic_AC_CLResControlMode& out) {
    convert(in, static_cast<datatypes::Dynamic_AC_CLResControlMode&>(out));

    convert(in.EVSEMaximumChargePower, out.max_charge_power);
    CB2CPP_CONVERT_IF_USED(in.EVSEMaximumChargePower_L2, out.max_charge_power_L2);
    CB2CPP_CONVERT_IF_USED(in.EVSEMaximumChargePower_L3, out.max_charge_power_L3);

    convert(in.EVSEMaximumDischargePower, out.max_discharge_power);
    CB2CPP_CONVERT_IF_USED(in.EVSEMaximumDischargePower_L2, out.max_discharge_power_L2);
    CB2CPP_CONVERT_IF_USED(in.EVSEMaximumDischargePower_L3, out.max_discharge_power_L3);

    CB2CPP_CONVERT_IF_USED(in.DSOMaximumDischargePower, out.dso_discharge_power);
    CB2CPP_CONVERT_IF_USED(in.DSOMaximumDischargePower_L2, out.dso_discharge_power_L2);
    CB2CPP_CONVERT_IF_USED(in.DSOMaximumDischargePower_L3, out.dso_discharge_power_L3);

    CB2CPP_CONVERT_IF_USED(in.DSOQSetpoint, out.dso_q_setpoint);
    CB2CPP_CONVERT_IF_USED(in.DSOCosPhiSetpoint, out.dso_cos_phi_setpoint);
}

struct ControlModeVisitor {
    using ScheduledCM = datatypes::Scheduled_AC_CLResControlMode;
    using BPT_ScheduledCM = datatypes::BPT_Scheduled_AC_CLResControlMode;
    using DynamicCM = datatypes::Dynamic_AC_CLResControlMode;
    using BPT_DynamicCM = datatypes::BPT_Dynamic_AC_CLResControlMode;
    using DER_ScheduledCM = datatypes::DER_Scheduled_AC_CLResControlMode;
    using DER_DynamicCM = datatypes::DER_Dynamic_AC_CLResControlMode;

    ControlModeVisitor(iso20_ac_der_iec_AC_ChargeLoopResType& res_) : res(res_) {};

    void operator()(const ScheduledCM& in) {
        auto& out = res.Scheduled_AC_CLResControlMode;
        init_iso20_ac_der_iec_Scheduled_AC_CLResControlModeType(&out);
        convert(in, out);
        CB_SET_USED(res.Scheduled_AC_CLResControlMode);
    }

    void operator()(const BPT_ScheduledCM& in) {
        auto& out = res.BPT_Scheduled_AC_CLResControlMode;
        init_iso20_ac_der_iec_BPT_Scheduled_AC_CLResControlModeType(&out);
        convert(in, out);
        CB_SET_USED(res.BPT_Scheduled_AC_CLResControlMode);
    }

    void operator()(const DER_ScheduledCM& in) {
        auto& out = res.DER_Scheduled_AC_CLResControlMode;
        init_iso20_ac_der_iec_DER_Scheduled_AC_CLResControlModeType(&out);
        convert(in, out);
        CB_SET_USED(res.DER_Scheduled_AC_CLResControlMode);
    }

    void operator()(const DynamicCM& in) {
        auto& out = res.Dynamic_AC_CLResControlMode;
        init_iso20_ac_der_iec_Dynamic_AC_CLResControlModeType(&out);
        convert(in, out);
        CB_SET_USED(res.Dynamic_AC_CLResControlMode);
    }

    void operator()(const BPT_DynamicCM& in) {
        auto& out = res.BPT_Dynamic_AC_CLResControlMode;
        init_iso20_ac_der_iec_BPT_Dynamic_AC_CLResControlModeType(&out);
        convert(in, out);
        CB_SET_USED(res.BPT_Dynamic_AC_CLResControlMode);
    }

    void operator()(const DER_DynamicCM& in) {
        auto& out = res.DER_Dynamic_AC_CLResControlMode;
        init_iso20_ac_der_iec_DER_Dynamic_AC_CLResControlModeType(&out);
        convert(in, out);
        CB_SET_USED(res.DER_Dynamic_AC_CLResControlMode);
    }

private:
    iso20_ac_der_iec_AC_ChargeLoopResType& res;
};

template <> void convert(const DER_AC_ChargeLoopResponse& in, struct iso20_ac_der_iec_AC_ChargeLoopResType& out) {
    init_iso20_ac_der_iec_AC_ChargeLoopResType(&out);

    convert(in.header, out.Header);
    cb_convert_enum(in.response_code, out.ResponseCode);

    CPP2CB_CONVERT_IF_USED(in.status, out.EVSEStatus);
    CPP2CB_CONVERT_IF_USED(in.meter_info, out.MeterInfo);
    CPP2CB_CONVERT_IF_USED(in.receipt, out.Receipt);

    CPP2CB_CONVERT_IF_USED(in.target_frequency, out.EVSETargetFrequency);

    std::visit(ControlModeVisitor(out), in.control_mode);
}

template <> void convert(const struct iso20_ac_der_iec_AC_ChargeLoopResType& in, DER_AC_ChargeLoopResponse& out) {
    convert(in.Header, out.header);
    cb_convert_enum(in.ResponseCode, out.response_code);
    CB2CPP_CONVERT_IF_USED(in.MeterInfo, out.meter_info);
    CB2CPP_CONVERT_IF_USED(in.Receipt, out.receipt);
    CB2CPP_CONVERT_IF_USED(in.EVSEStatus, out.status);
    CB2CPP_CONVERT_IF_USED(in.EVSETargetFrequency, out.target_frequency);

    if (in.Scheduled_AC_CLResControlMode_isUsed) {
        convert(in.Scheduled_AC_CLResControlMode, out.control_mode.emplace<datatypes::Scheduled_AC_CLResControlMode>());
    } else if (in.BPT_Scheduled_AC_CLResControlMode_isUsed) {
        convert(in.BPT_Scheduled_AC_CLResControlMode,
                out.control_mode.emplace<datatypes::BPT_Scheduled_AC_CLResControlMode>());
    } else if (in.DER_Scheduled_AC_CLResControlMode_isUsed) {
        convert(in.DER_Scheduled_AC_CLResControlMode,
                out.control_mode.emplace<datatypes::DER_Scheduled_AC_CLResControlMode>());
    } else if (in.Dynamic_AC_CLResControlMode_isUsed) {
        convert(in.Dynamic_AC_CLResControlMode, out.control_mode.emplace<datatypes::Dynamic_AC_CLResControlMode>());
    } else if (in.BPT_Dynamic_AC_CLResControlMode_isUsed) {
        convert(in.BPT_Dynamic_AC_CLResControlMode,
                out.control_mode.emplace<datatypes::BPT_Dynamic_AC_CLResControlMode>());
    } else if (in.DER_Dynamic_AC_CLResControlMode_isUsed) {
        convert(in.DER_Dynamic_AC_CLResControlMode,
                out.control_mode.emplace<datatypes::DER_Dynamic_AC_CLResControlMode>());
    } else {
        // should not happen
        assert(false);
    }
}

template <> int serialize_to_exi(const DER_AC_ChargeLoopResponse& in, exi_bitstream_t& out) {
    iso20_ac_der_iec_exiDocument doc{};
    init_iso20_ac_der_iec_exiDocument(&doc);

    CB_SET_USED(doc.AC_ChargeLoopRes);

    convert(in, doc.AC_ChargeLoopRes);

    return encode_iso20_ac_der_iec_exiDocument(&out, &doc);
}

template <> size_t serialize(const DER_AC_ChargeLoopResponse& in, const io::StreamOutputView& out) {
    return serialize_helper(in, out);
}

template <> void insert_type(VariantAccess& va, const struct iso20_ac_der_iec_AC_ChargeLoopResType& in) {
    va.insert_type<DER_AC_ChargeLoopResponse>(in);
}

} // namespace iso15118::message_20
