<?php

/*
 * This code is an addon for GOsa² (https://gosa.gonicus.de)
 * https://github.com/gosa-project/gosa-plugins-privacyidea/
 * Copyright (C) 2023 Daniel Teichmann <daniel.teichmann@das-netzwerkteam.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// This is a dirty hack for development purposes.
// Make sure to require 'privacyidea/privacyidea-php-client' via composer and
// then copy ./vendor/privacyidea/ to /usr/share/gosa/.
require_once("/usr/share/gosa/vendor/privacyidea/privacyidea-php-client/src/PrivacyIDEA.php");
require_once("/usr/share/gosa/vendor/privacyidea/privacyidea-php-client/src/PIResponse.php");
require_once("/usr/share/gosa/vendor/privacyidea/privacyidea-php-client/src/PILog.php");
require_once("/usr/share/gosa/vendor/privacyidea/privacyidea-php-client/src/PIChallenge.php");
require_once("/usr/share/gosa/vendor/privacyidea/privacyidea-php-client/src/PIBadRequestException.php");
require_once("/usr/share/gosa/vendor/privacyidea/privacyidea-php-client/src/AuthenticationStatus.php");

class PrivacyIdeaUtils
{
    private PrivacyIDEA $pi;

    public function __construct()
    {
        // TODO: Load privacyIDEA server URL from settings.
        $pi_server_url = "localhost:5000/";

        $this->pi = new PrivacyIDEA($_SERVER['HTTP_USER_AGENT'], $pi_server_url);
    }

    /*!
     * \brief  Dirty hacked-together function to test the validateCheck endpoint of privacyIDEA.
     */
    public function validateCheck($user, $pass, $realm = "")
    {
        assert('string' === gettype($user));
        assert('string' === gettype($pass));
        assert('string' === gettype($realm));

        $this->pi->realm = $realm;

        try {
            $response = $this->pi->validateCheck($user, $pass);
        } catch (PIBadRequestException $e) {
            echo "<h1>Exception while validating!</h1><br>" .
                 "<p>" . $e->getMessage() . "</p>";

            echo "<br>";
        }
        var_dump($response);
    }
}
