module.exports = (request, response, schema) => {
  console.dir(request.body);
  let { error, value } = schema.validate(request.body);
  if (error) {
    response.writeHead(400, {'Content-Type': 'text/plain'});
    response.end('Invalid request.');
  }
  return { error, value };
}