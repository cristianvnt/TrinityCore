DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_pri_spectral_illusion_aura', 'spell_gen_inherit_masters_threat_list');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(1250385, 'spell_pri_spectral_illusion_aura'),
(58838, 'spell_gen_inherit_masters_threat_list');

DELETE FROM `spell_proc` WHERE `SpellId` IN (1250378);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(1250378,0x00,6,0x00004000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0,0,0,0); -- Spectral Illusion

UPDATE `creature_template` SET `faction`=35, `BaseAttackTime`=1800, `unit_flags2`=0x800, `unit_flags3`=0x1000000, `ScriptName`="npc_pet_pri_spectral_illusion" WHERE `entry`=250373; -- Spectral Illusion
