DELIMITER $$

CREATE FUNCTION levenshtein_similarity(str1 TEXT, str2 TEXT)
    RETURNS FLOAT
    DETERMINISTIC
    BEGIN
        DECLARE str1_len, str2_len, i, j, c, c_temp, cost INT;
        DECLARE str1_char CHAR;
        DECLARE cv0, cv1 VARBINARY(256);

        SET str1_len = CHAR_LENGTH(str1), str2_len = CHAR_LENGTH(str2), cv1 = 0x00, j = 1, i = 1, c = 0;

        IF str1 = str2 THEN
            RETURN 0;
        ELSEIF str1_len = 0 THEN
            RETURN str2_len;
        ELSEIF str2_len = 0 THEN
            RETURN str1_len;
        ELSE
            WHILE j <= str2_len DO
                SET cv1 = CONCAT(cv1, UNHEX(HEX(j))), j = j + 1;
            END WHILE;
            WHILE i <= str1_len DO
                SET str1_char = SUBSTRING(str1, i, 1), c = i, cv0 = UNHEX(HEX(i)), j = 1;
                WHILE j <= str2_len DO
                    SET c = c + 1;
                    IF str1_char = SUBSTRING(str2, j, 1) THEN
                        SET cost = 0; ELSE SET cost = 1;
                    END IF;
                    SET c_temp = CONV(HEX(SUBSTRING(cv1, j, 1)), 16, 10) + cost;
                    IF c > c_temp THEN SET c = c_temp; END IF;
                    SET c_temp = CONV(HEX(SUBSTRING(cv1, j+1, 1)), 16, 10) + 1;
                    IF c > c_temp THEN
                        SET c = c_temp;
                    END IF;
                    SET cv0 = CONCAT(cv0, UNHEX(HEX(c))), j = j + 1;
                END WHILE;
                SET cv1 = cv0, i = i + 1;
            END WHILE;
        END IF;
        
        RETURN 1 - c / GREATEST(str1_len, str2_len);
    END$$

DELIMITER ;