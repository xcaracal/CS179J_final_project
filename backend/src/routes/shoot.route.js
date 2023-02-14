const express = require('express');
const Joi = require('joi');
const router = express.Router();

const schema = null;

router.post('/', function(request, response) {
  console.log('POST /shoot');
  console.dir(request.params);
  const id = 1;
  response.writeHead(200, {'Content-Type': 'text/plain'});
  response.end(`The gun with ID ${id} shoots!`);
});

module.exports = router;
