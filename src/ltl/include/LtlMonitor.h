#pragma once

class LtlMonitor
{
 public:
    static std::optional<LtlMonitor> getMonitor(ProgramDefinitionContext *ctx);
}
