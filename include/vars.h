#pragma once
#include <cstdio>
#include <unistd.h>
#include <chrono>
#include <string>
#include <vector>
#include <map>

struct Econet_Mqtt
{
    std::string pub_huw_temp;
    std::string pub_huw_pump_mode;
    std::string pub_huw_temp_hysteresis;
    std::string pub_huw_container_disinfection;
    std::string pub_boiler_temp;
    std::string pub_boiler_on_off;
    std::string pub_boiler_max_power_kw;
    std::string pub_boiler_mid_power_kw;
    std::string pub_boiler_min_power_kw;
    std::string pub_boiler_max_power_fan;
    std::string pub_boiler_mid_power_fan;
    std::string pub_boiler_min_power_fan;
    std::string pub_mixer_temp;
    std::string pub_room_thermostat_summer_winter_mode;
    std::string pub_room_thermostat_night_temp;
    std::string pub_room_thermostat_day_temp;
    std::string pub_room_thermostat_operating_mode;
    std::string pub_room_thermostat_hysteresis;
    std::string sub_get_operating_status;
    std::string sub_get_huw_temp;
    std::string sub_get_feeder_temp;
    std::string sub_get_boiler_temp;
    std::string sub_get_weather_temp;
    std::string sub_get_exhaust_temp;
    std::string sub_get_mixer_temp;
    std::string sub_get_boiler_return_temp;
    std::string sub_get_upper_buffer_temp;
    std::string sub_get_lower_buffer_temp;
    std::string sub_get_flame_sensor;
    std::string sub_get_ecoster_home_temp;
    std::string sub_get_ecoster_home_temp_target;
    std::string sub_get_huw_temp_target;
    std::string sub_get_boiler_temp_target;
    std::string sub_get_mixer_temp_target;
    std::string sub_get_fuel_level;
    std::string sub_get_fan_out_power;
    std::string sub_get_fan_in_power;
    std::string sub_get_huw_pomp_state;
    std::string sub_get_boiler_pomp_state;
    std::string sub_get_fuel_stream;
    std::string sub_get_boiler_power_kw;
    std::string sub_get_power_max_time;
    std::string sub_get_power_medium_time;
    std::string sub_get_power_min_time;
    std::string sub_get_feeder_time;
    std::string sub_get_ignitions;
    std::string sub_get_ignitions_fails;
    std::string sub_get_huw_pump_mode;
    std::string sub_get_huw_temp_hysteresis;
    std::string sub_get_huw_container_disinfection;
    std::string sub_get_boiler_on_off;
    std::string sub_get_boiler_max_power_kw;
    std::string sub_get_boiler_mid_power_kw;
    std::string sub_get_boiler_min_power_kw;
    std::string sub_get_boiler_max_power_fan;
    std::string sub_get_boiler_mid_power_fan;
    std::string sub_get_boiler_min_power_fan;
    std::string sub_get_room_thermostat_summer_winter_mode;
    std::string sub_get_room_thermostat_night_temp;
    std::string sub_get_room_thermostat_day_temp;
    std::string sub_get_room_thermostat_operating_mode;
    std::string sub_get_room_thermostat_hysteresis="0.5";
};

























struct Ecomax_920_Frame{
    uint8_t frame_begine = 0; 
    uint16_t frame_size = 0;

    uint8_t message_dst = 0;
    uint8_t message_src = 0;
    uint8_t nn_5 = 0;
    uint8_t nn_6 = 0;
    uint8_t payload_type = 0;
    uint8_t nn_8 = 0;
    uint8_t nn_9 = 0;
    uint8_t nn_10 = 0;
    uint8_t nn_11 = 0;
    uint8_t nn_12 = 0;
    uint8_t nn_13 = 0;
    uint8_t nn_14 = 0;
    uint8_t nn_15 = 0;
    uint8_t nn_16 = 0;
    uint8_t nn_17 = 0;
    uint8_t nn_18 = 0;
    uint8_t nn_19 = 0;
    uint8_t nn_20 = 0;
    uint8_t nn_21 = 0;
    uint8_t nn_22 = 0;
    uint8_t nn_23 = 0;
    uint8_t nn_24 = 0;
    uint8_t nn_25 = 0;
    uint8_t nn_26 = 0;
    uint8_t nn_27 = 0;
    uint8_t nn_28 = 0;
    uint8_t nn_29 = 0;
    uint8_t nn_30 = 0;
    uint8_t nn_31 = 0;
    uint8_t nn_32 = 0;
    uint8_t nn_33 = 0;
    uint8_t nn_34 = 0;
    uint8_t nn_35 = 0;
    uint8_t nn_36 = 0;
    uint8_t nn_37 = 0;
    uint8_t operating_status = 0; //29
    uint8_t nn_39 = 0;
    uint8_t nn_40 = 0;
    uint8_t nn_41 = 0;
    uint8_t nn_42 = 0;
    uint8_t nn_43 = 0;
    uint8_t nn_44 = 0;
    uint8_t nn_45 = 0;
    uint8_t nn_46 = 0;
    uint8_t nn_47 = 0;
    uint8_t nn_48 = 0;
    uint8_t nn_49 = 0;
    uint8_t nn_50 = 0;
    uint8_t nn_51 = 0;
    uint8_t nn_52 = 0;
    uint8_t nn_53 = 0;
    uint8_t nn_54 = 0;
    uint8_t nn_55 = 0;
    uint8_t nn_56 = 0;
    uint8_t nn_57 = 0;
    uint8_t nn_58 = 0;
    uint8_t nn_59 = 0;
    uint8_t nn_60 = 0;
    uint8_t nn_61 = 0;
    uint8_t nn_62 = 0;
    uint8_t nn_63 = 0;
    uint8_t nn_64 = 0;
    uint8_t nn_65 = 0;
    uint8_t nn_66 = 0;
    uint8_t nn_67 = 0;
    uint8_t nn_68 = 0;
    uint8_t nn_69 = 0;
    uint8_t nn_70 = 0;
    uint8_t nn_71 = 0;
    uint8_t nn_72 = 0;
    uint8_t nn_73 = 0;
    uint8_t nn_74 = 0;
    uint8_t nn_75 = 0;
    uint8_t nn_76 = 0;
    uint8_t nn_77 = 0;
    uint8_t nn_78 = 0;
    uint8_t nn_79 = 0;
    uint8_t nn_80 = 0;
    uint8_t nn_81 = 0;
    uint8_t nn_82 = 0;
    uint8_t nn_83 = 0;
    uint8_t nn_84 = 0;
    uint8_t nn_85 = 0;
    float huw_temp = 0; 



    float mixer_temp = 0; 



    float weather_temp = 0; 



    float boiler_return_temp = 0; 



    float exhaust_temp = 0; 



    float feeder_temp = 0;



    float boiler_temp = 0; 



    float flame_sensor = 0; 



    float upper_buffer_temp = 0; 



    float lower_buffer_temp = 0; 



    uint8_t nn_126 = 0;
    uint8_t nn_127 = 0;
    uint8_t nn_128 = 0;
    uint8_t nn_129 = 0; 
    uint8_t nn_130 = 0;
    uint8_t nn_131 = 0;
    uint8_t nn_132 = 0;
    uint8_t nn_133 = 0;
    uint8_t nn_134 = 0;
    uint8_t nn_135 = 0;
    uint8_t nn_136 = 0;
    uint8_t nn_137 = 0;
    uint8_t nn_138 = 0;
    uint8_t nn_139 = 0;
    uint8_t nn_140 = 0;
    uint8_t nn_141 = 0;
    uint8_t nn_142 = 0;
    uint8_t nn_143 = 0;
    uint8_t nn_144 = 0;
    uint8_t nn_145 = 0;
    uint8_t nn_146 = 0;
    uint8_t nn_147 = 0;
    uint8_t nn_148 = 0;
    uint8_t nn_149 = 0;
    uint8_t nn_150 = 0;
    uint8_t nn_151 = 0;
    uint8_t nn_152 = 0;
    uint8_t nn_153 = 0;
    uint8_t nn_154 = 0;
    uint8_t nn_155 = 0;
    uint8_t nn_156 = 0;
    uint8_t nn_157 = 0;
    uint8_t nn_158 = 0;
    uint8_t nn_159 = 0;
    uint8_t nn_160 = 0;
    uint8_t nn_161 = 0;
    uint8_t nn_162 = 0;
    uint8_t nn_163 = 0;
    uint8_t nn_164 = 0;
    uint8_t nn_165 = 0;
    uint8_t nn_166 = 0;
    uint8_t nn_167 = 0;
    uint8_t nn_168 = 0;
    uint8_t nn_169 = 0;
    uint8_t nn_170 = 0;
    uint8_t nn_171 = 0;
    uint8_t nn_172 = 0;
    uint8_t nn_173 = 0;
    uint8_t nn_174 = 0;
    uint8_t huw_temp_target = 0; 
    uint8_t nn_176 = 0;
    uint8_t nn_177 = 0;
    uint8_t nn_178 = 0;
    uint8_t boiler_temp_target = 0;
    uint8_t nn_180 = 0;
    uint8_t nn_181 = 0;
    uint8_t nn_182 = 0;
    uint8_t nn_183 = 0;
    uint8_t nn_184 = 0;
    uint8_t nn_185 = 0;
    uint8_t nn_186 = 0;
    uint8_t nn_187 = 0;
    uint8_t nn_188 = 0;
    uint8_t nn_189 = 0;
    uint8_t nn_190 = 0;
    uint8_t nn_191 = 0;
    uint8_t nn_192 = 0;
    uint8_t nn_193 = 0;
    uint8_t nn_194 = 0;
    uint8_t nn_195 = 0;
    uint8_t nn_196 = 0;
    uint8_t nn_197 = 0;
    uint8_t nn_198 = 0;
    uint8_t nn_199 = 0;
    uint8_t nn_200 = 0;
    uint8_t nn_201 = 0;
    uint8_t huw_pomp_state = 0;
    uint8_t nn_203 = 0;
    uint8_t nn_204 = 0;
    uint8_t nn_205 = 0;
    uint8_t nn_206 = 0;
    uint8_t nn_207 = 0;
    uint8_t nn_208 = 0;
    uint8_t nn_209 = 0;
    uint8_t nn_210 = 0;
    uint8_t nn_211 = 0;
    uint8_t nn_212 = 0;
    uint8_t nn_213 = 0;
    uint8_t nn_214 = 0;
    uint8_t nn_215 = 0;
    uint8_t nn_216 = 0;
    uint8_t nn_217 = 0;
    uint8_t nn_218 = 0;
    uint8_t nn_219 = 0;
    uint8_t nn_220 = 0;
    uint8_t nn_221 = 0;
    uint8_t nn_222 = 0;
    uint8_t nn_223 = 0;
    uint8_t nn_224 = 0;
    uint8_t fuel_level = 0;
    uint8_t nn_226 = 0;
    uint8_t nn_227 = 0;
    uint8_t nn_228 = 0;
    uint8_t nn_229 = 0;
    uint8_t nn_230 = 0;
    uint8_t nn_231 = 0;
    uint8_t nn_232 = 0;
    uint8_t nn_233 = 0;
    uint8_t nn_234 = 0;
    uint8_t nn_235 = 0;
    uint8_t nn_236 = 0;
    uint8_t nn_237 = 0;
    uint8_t nn_238 = 0;
    uint8_t nn_239 = 0;
    uint8_t nn_240 = 0;
    uint8_t nn_241 = 0;
    uint8_t nn_242 = 0;
    uint8_t nn_243 = 0;
    uint8_t nn_244 = 0;
    uint8_t nn_245 = 0;
    uint8_t nn_246 = 0;
    uint8_t nn_247 = 0;
    uint8_t nn_248 = 0;
    uint8_t nn_249 = 0;
    uint8_t nn_250 = 0;
    uint8_t nn_251 = 0;
    uint8_t nn_252 = 0;
    uint8_t nn_253 = 0;
    uint8_t nn_254 = 0;
    uint8_t nn_255 = 0;
    uint8_t nn_256 = 0;
    uint8_t nn_257 = 0;
    uint8_t nn_258 = 0;
    uint8_t nn_259 = 0;
    uint8_t nn_260 = 0;
    uint8_t nn_261 = 0;
    uint8_t fan_in_power = 0;
    uint8_t fan_out_power = 0;  
    float boiler_power_kw= 0;



    float fuel_stream = 0;  



    uint8_t nn_272 = 0;
    uint8_t nn_273 = 0;
    uint8_t boiler_pomp_state = 0; 
    uint16_t power_max_time = 0; 

    uint16_t power_medium_time = 0;

    uint16_t power_min_time = 0;

    uint16_t feeder_time = 0;

    uint16_t ignitions = 0;

    uint16_t ignitions_fails = 0;

    uint8_t nn_287 = 0;
    uint8_t nn_288 = 0;
    uint8_t nn_289 = 0;
    uint8_t nn_290 = 0;
    uint8_t nn_291 = 0;
    uint8_t nn_292 = 0;
    uint8_t nn_293 = 0;
    uint8_t nn_294 = 0;
    uint8_t nn_295 = 0;
    uint8_t nn_296 = 0;
    uint8_t nn_297 = 0;
    uint8_t nn_298 = 0;
    uint8_t nn_299 = 0;
    uint8_t nn_300 = 0;
    uint8_t nn_301 = 0;
    uint8_t nn_302 = 0;
    uint8_t nn_303 = 0;
    uint8_t nn_304 = 0;
    uint8_t nn_305 = 0;
    uint8_t nn_306 = 0;
    uint8_t nn_307 = 0;
    uint8_t nn_308 = 0;
    uint8_t nn_309 = 0;
    uint8_t nn_310 = 0;
    uint8_t nn_311 = 0;
    uint8_t nn_312 = 0;
    uint8_t nn_313 = 0;
    uint8_t nn_314 = 0;
    uint8_t nn_315 = 0;
    uint8_t nn_316 = 0;
    uint8_t nn_317 = 0;
    uint8_t nn_318 = 0;
    uint8_t nn_319 = 0;
    uint8_t nn_320 = 0;
    uint8_t nn_321 = 0;
    uint8_t nn_322 = 0;
    uint8_t nn_323 = 0;
    uint8_t nn_324 = 0;
    uint8_t nn_325 = 0;
    uint8_t nn_326 = 0;
    uint8_t nn_327 = 0;
    uint8_t nn_328 = 0;
    uint8_t frame_crc = 0;
    uint8_t frame_end_signature = 0;
};



struct Ecomax_920_Frame_Header{
    //uint8_t frame_begine = 0; 	// 0
    uint16_t frame_size = 0;    // 1
    uint8_t dst_address = 0;    // 3
    uint8_t src_address = 0;    // 4
    uint8_t nn_5 = 0;           // 5
    uint8_t nn_6 = 0;           // 6
    uint8_t payload_type = 0;   // 7
    uint8_t frame_begine = 0; 	// 0
};



struct Ecomax_920_Live_Data_Frame_payload{
    uint8_t nn_0 = 0;
    uint8_t nn_1 = 0;
    uint8_t nn_2 = 0;
    uint8_t nn_3 = 0;
    uint8_t nn_4 = 0;
    uint8_t nn_5 = 0;
    uint8_t nn_6 = 0;
    uint8_t nn_7 = 0;
    uint8_t nn_8 = 0;
    uint8_t nn_9 = 0;
    uint8_t nn_10 = 0;
    uint8_t nn_11 = 0;
    uint8_t nn_12 = 0;
    uint8_t nn_13 = 0;
    uint8_t nn_14 = 0;
    uint8_t nn_15 = 0;
    uint8_t nn_16 = 0;
    uint8_t nn_17 = 0;
    uint8_t nn_18 = 0;
    uint8_t nn_19 = 0;
    uint8_t nn_20 = 0;
    uint8_t nn_21 = 0;
    uint8_t nn_22 = 0;
    uint8_t nn_23 = 0;
    uint8_t nn_24 = 0;
    uint8_t nn_25 = 0;
    uint8_t nn_26 = 0;
    uint8_t nn_27 = 0;
    uint8_t nn_28 = 0;
    uint8_t operating_status = 0; //29
    uint8_t nn_30 = 0;
    uint8_t nn_31 = 0;
    uint8_t nn_32 = 0;
    uint8_t nn_33 = 0;
    uint8_t nn_34 = 0;
    uint8_t nn_35 = 0;
    uint8_t nn_36 = 0;
    uint8_t nn_37 = 0;
    uint8_t nn_38 = 0;
    uint8_t nn_39 = 0;
    uint8_t nn_40 = 0;
    uint8_t nn_41 = 0;
    uint8_t nn_42 = 0;
    uint8_t nn_43 = 0;
    uint8_t nn_44 = 0;
    uint8_t nn_45 = 0;
    uint8_t nn_46 = 0;
    uint8_t nn_47 = 0;
    uint8_t nn_48 = 0;
    uint8_t nn_49 = 0;
    uint8_t nn_50 = 0;
    uint8_t nn_51 = 0;
    uint8_t nn_52 = 0;
    uint8_t nn_53 = 0;
    uint8_t nn_54 = 0;
    uint8_t nn_55 = 0;
    uint8_t nn_56 = 0;
    uint8_t nn_57 = 0;
    uint8_t nn_58 = 0;
    uint8_t nn_59 = 0;
    uint8_t nn_60 = 0;
    uint8_t nn_61 = 0;
    uint8_t nn_62 = 0;
    uint8_t nn_63 = 0;
    uint8_t nn_64 = 0;
    uint8_t nn_65 = 0;
    uint8_t nn_66 = 0;
    uint8_t nn_67 = 0;
    uint8_t nn_68 = 0;
    uint8_t nn_69 = 0;
    uint8_t nn_70 = 0;
    uint8_t nn_71 = 0;
    uint8_t nn_72 = 0;
    uint8_t nn_73 = 0;
    uint8_t nn_74 = 0;
    uint8_t nn_75 = 0;
    uint8_t nn_76 = 0;
    uint8_t nn_77 = 0;
    float huw_temp = 0;   // 78



    float mixer_temp = 0;  // 82



    float weather_temp = 0;  //86



    float boiler_return_temp = 0; // 90 



    float exhaust_temp = 0;   // 94 



    float feeder_temp = 0;  // 98



    float boiler_temp = 0;  // 102



    float flame_sensor = 0;  // 106



    float upper_buffer_temp = 0;  // 110 



    float lower_buffer_temp = 0;  // 114  



    uint8_t nn_118 = 0;  
    uint8_t nn_119 = 0;
    uint8_t nn_120 = 0;
    uint8_t nn_121 = 0; 
    uint8_t nn_122 = 0;
    uint8_t nn_123 = 0;
    uint8_t nn_124 = 0;
    uint8_t nn_125 = 0;
    uint8_t nn_126 = 0;
    uint8_t nn_127 = 0;
    uint8_t nn_128 = 0;
    uint8_t nn_129 = 0;
    uint8_t nn_130 = 0;
    uint8_t nn_131 = 0;
    uint8_t nn_132 = 0;
    uint8_t nn_133 = 0;
    uint8_t nn_134 = 0;
    uint8_t nn_135 = 0;
    uint8_t nn_136 = 0;
    uint8_t nn_137 = 0;
    uint8_t nn_138 = 0;
    uint8_t nn_139 = 0;
    uint8_t nn_140 = 0;
    uint8_t nn_141 = 0;
    uint8_t nn_142 = 0;
    uint8_t nn_143 = 0;
    uint8_t nn_144 = 0;
    uint8_t nn_145 = 0;
    uint8_t nn_146 = 0;
    uint8_t nn_147 = 0;
    uint8_t nn_148 = 0;
    uint8_t nn_149 = 0;
    uint8_t nn_150 = 0;
    uint8_t nn_151 = 0;
    uint8_t nn_152 = 0;
    uint8_t nn_153 = 0;
    uint8_t nn_154 = 0;
    uint8_t nn_155 = 0;
    uint8_t nn_156 = 0;
    uint8_t nn_157 = 0;
    uint8_t nn_158 = 0;
    uint8_t nn_159 = 0;
    uint8_t nn_160 = 0;
    uint8_t nn_161 = 0;
    uint8_t nn_162 = 0;
    uint8_t nn_163 = 0;
    uint8_t nn_164 = 0;
    uint8_t nn_165 = 0;
    uint8_t mixer_temp_target = 0;  // 166
    uint8_t huw_temp_target = 0;  // 167 
    uint8_t nn_168 = 0;
    uint8_t nn_169 = 0;
    uint8_t nn_170 = 0;
    uint8_t nn_171 = 0;
    uint8_t boiler_temp_target = 0; // 172
    uint8_t nn_173 = 0;
    uint8_t nn_174 = 0;
    uint8_t nn_175 = 0;
    uint8_t nn_176 = 0;
    uint8_t nn_177 = 0;
    uint8_t nn_178 = 0;
    uint8_t nn_179 = 0;
    uint8_t nn_180 = 0;
    uint8_t nn_181 = 0;
    uint8_t nn_182 = 0;
    uint8_t nn_183 = 0;
    uint8_t nn_184 = 0;
    uint8_t nn_185 = 0;
    uint8_t nn_186 = 0;
    uint8_t nn_187 = 0;
    uint8_t nn_188 = 0;
    uint8_t nn_189 = 0;
    uint8_t nn_190 = 0;
    uint8_t nn_191 = 0;
    uint8_t nn_192 = 0;
    uint8_t nn_193 = 0;
    uint8_t nn_194 = 0;
    uint8_t huw_pomp_state = 0;  // 195
    uint8_t nn_196 = 0;
    uint8_t nn_197 = 0;
    uint8_t nn_198 = 0;
    uint8_t nn_199 = 0;
    uint8_t nn_200 = 0;
    uint8_t nn_201 = 0;
    uint8_t nn_202 = 0;
    uint8_t nn_203 = 0;
    uint8_t nn_204 = 0;
    uint8_t nn_205 = 0;
    uint8_t nn_206 = 0;
    uint8_t nn_207 = 0;
    uint8_t nn_208 = 0;
    uint8_t nn_209 = 0;
    uint8_t nn_210 = 0;
    uint8_t nn_211 = 0;
    uint8_t nn_212 = 0;
    uint8_t nn_213 = 0;
    uint8_t nn_214 = 0;
    uint8_t nn_215 = 0;
    uint8_t nn_216 = 0;
    uint8_t fuel_level = 0; // 217
    uint8_t nn_218 = 0;
    uint8_t nn_219 = 0;
    uint8_t nn_220 = 0;
    uint8_t nn_221 = 0;
    uint8_t nn_222 = 0;
    uint8_t nn_223 = 0;
    uint8_t nn_224 = 0;
    uint8_t nn_225 = 0;
    uint8_t nn_226 = 0;
    uint8_t nn_227 = 0;
    uint8_t nn_228 = 0;
    uint8_t nn_229 = 0;
    uint8_t nn_230 = 0;
    uint8_t nn_231 = 0;
    uint8_t nn_232 = 0;
    uint8_t nn_233 = 0;
    uint8_t nn_234 = 0;
    uint8_t nn_235 = 0;
    uint8_t nn_236 = 0;
    uint8_t nn_237 = 0;
    uint8_t nn_238 = 0;
    uint8_t nn_239 = 0;
    uint8_t nn_240 = 0;
    uint8_t nn_241 = 0;
    uint8_t nn_242 = 0;
    uint8_t nn_243 = 0;
    uint8_t nn_244 = 0;
    uint8_t nn_245 = 0;
    uint8_t nn_246 = 0;
    uint8_t nn_247 = 0;
    uint8_t nn_248 = 0;
    uint8_t nn_249 = 0;
    uint8_t nn_250 = 0;
    uint8_t nn_251 = 0;
    uint8_t nn_252 = 0;
    uint8_t nn_253 = 0;
    uint8_t fan_in_power = 0; 	// 254
    uint8_t fan_out_power = 0;  // 255 
    float boiler_power_kw= 0;	// 256 



    float fuel_stream = 0;  	// 260



    uint8_t nn_264 = 0;
    uint8_t boiler_pomp_state = 0; // 265
    uint16_t power_max_time = 0;   // 266 	

    uint16_t power_medium_time = 0;  // 268

    uint16_t power_min_time = 0;   // 270

    uint16_t feeder_time = 0;      // 272

    uint16_t ignitions = 0;	   // 274

    uint16_t ignitions_fails = 0;  // 276

    uint8_t nn_278 = 0; 
    uint8_t nn_279 = 0;
    uint8_t nn_280 = 0;
    uint8_t nn_281 = 0;
    uint8_t nn_282 = 0;
    uint8_t nn_283 = 0;
    uint8_t nn_284 = 0;
    uint8_t nn_285 = 0;
    uint8_t nn_286 = 0;
    uint8_t nn_287 = 0;
    uint8_t nn_288 = 0;
    uint8_t nn_289 = 0;
    uint8_t nn_290 = 0;
    uint8_t nn_291 = 0;
    uint8_t nn_292 = 0;
    uint8_t nn_293 = 0;
    uint8_t nn_294 = 0;
    uint8_t nn_295 = 0;
    uint8_t nn_296 = 0;
    uint8_t nn_297 = 0;
    uint8_t nn_298 = 0;
    uint8_t nn_299 = 0;
    uint8_t nn_300 = 0;
    uint8_t nn_301 = 0;
    uint8_t nn_302 = 0;
    uint8_t nn_303 = 0;
    uint8_t nn_304 = 0;
    uint8_t nn_305 = 0;
    uint8_t nn_306 = 0;
    uint8_t nn_307 = 0;
    uint8_t nn_308 = 0;
    uint8_t nn_309 = 0;
    uint8_t nn_310 = 0;
    uint8_t nn_311 = 0;
    uint8_t nn_312 = 0;
    uint8_t nn_313 = 0;
    uint8_t nn_314 = 0;
    uint8_t nn_315 = 0;
    uint8_t nn_316 = 0;
    uint8_t nn_317 = 0;
    uint8_t nn_318 = 0;
    uint8_t nn_319 = 0;
    uint8_t nn_320 = 0;
    uint8_t frame_crc = 0;
    uint8_t frame_end_signature = 0;
    };









struct EcoNet_cfg
{
    std::string serial_file;
    int boudrate;
    int remove_lead_zero;
};
struct Ecoster_payload
{
    float home_temp_target = 0; 
    float home_temp = 0;
    float ecoster_1_temp = 0;
    float ecoster_2_temp = 0;
};
struct Mqtt_config
{
    std::string ClientId;
    std::string ServerIp;
    std::string username;
    std::string password;
    int serverPort;
    std::string keepAliveTopic;
    std::string keepAliveMsg;
    std::string Substring;
    std::string Pubstring;
};


struct Ecomax920_payload{
    uint8_t payload_type = 0;      
    uint8_t operating_status = 0;   
    float  huw_temp = 0;        
    float  feeder_temp = 0;     
    float  boiler_temp = 0;        
    float  boiler_return_temp = 0;
    float  flame_sensor = 0;
    float  upper_buffer_temp = 0;
    float  lower_buffer_temp = 0;
    float  weather_temp = 0;   
    float  exhaust_temp = 0;    
    float  mixer_temp = 0;      
    float boiler_power_kw = 0;    
    float fuel_stream = 0;  
    uint8_t huw_temp_target = 0; 
    uint8_t boiler_temp_target = 0;  
    uint8_t mixer_temp_target = 0;  
    uint8_t fuel_level = 0;  
    uint8_t transmission = 0;
    uint8_t fan_in_power = 0;    
    uint8_t fan_out_power = 0;    
    uint8_t boiler_power = 0;
    uint8_t huw_pomp_state = 0;
    uint8_t boiler_pomp_state = 0;
    short power_max_time = 0;   
    short power_medium_time = 0; 
    short power_min_time = 0; 
    short feeder_time = 0; 
    short ignitions = 0; 
    short ignitions_fails = 0; 
};


